#include "Mesh.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <vector>
#include <memory>

#define PI 3.14159f

float degreesToRadians(float degrees) {
    return degrees * (PI / 180.f);
}

// window size
static const GLint WIDTH = 800, HEIGHT = 600;

std::vector<std::unique_ptr<Mesh>> meshArray;
GLuint shader, uniformModel, uniformProjection;

// vertex shader
static const char* vertexShader = "#version 330\n "
                                  "layout (location = 0) in vec3 pos; "
                                  "out vec4 vertexColor;"
                                  "uniform mat4 model; "
                                  "uniform mat4 projection; "
                                  "void main() {"
                                  "gl_Position = projection * model * vec4(pos, 1.0);"
                                  "vertexColor = vec4(clamp(pos, 0.0, 1.0), 1.0);"
                                  "}";
// fragment shader
static const char* fragmentShader = "#version 330\n"
                                    "in vec4 vertexColor;"
                                    "out vec4 color; "
                                    "void main() {"
                                    "color = vertexColor;"
                                    "}";

void createTriangle() {

    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            -1.f, -1.f, 0.f,
            0.f, -1.f, 1.f,
            1.f, -1.f, 0.f,
            0.f, 1.f, 0.f
    };

    meshArray.push_back(std::make_unique<Mesh>(vertices, 12, indices, 12));
}

void addShader (GLuint program, const char* shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, code, codeLength);
    glCompileShader(shader);

    GLint res = 0;
    GLchar log[1024] = { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (!res) {
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error shader compiling: " << log << "\n";
        return;
    }

    glAttachShader(program, shader);
}

void compileShaders () {
    shader = glCreateProgram();
    if (!shader) {
        std::cout << "Create shader program error!\n";
        return;
    }

    addShader(shader, vertexShader, GL_VERTEX_SHADER);
    addShader(shader, fragmentShader, GL_FRAGMENT_SHADER);

    GLint res = 0;
    GLchar log[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error linking program: " << log << "\n";
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error validation program: " << log << "\n";
        return;
    }

    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection");
}

int main() {
    std::cout << "Hello, World!" << std::endl;

    if (!glfwInit()) {
        std::cout << "GLFW initialization failed!\n";
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // no backwards compatibility?
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "title", NULL, NULL);
    if (!mainWindow) {
        std::cout << "GLFW window creation failed!\n";
        glfwTerminate();
        return 1;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!\n";
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    // setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    createTriangle();
    compileShaders();

    glm::mat4 projection = glm::perspective(45.f, static_cast<GLfloat>(bufferWidth) / static_cast<GLfloat>(bufferHeight), 0.1f, 100.f);

    float moveOffset = 0.f, moveDelta = 0.005f, maxMoveOffset = 0.5f;
    bool addDelta = true;

    float rotationAngle = 0.f, rotationAngleDelta = 0.5f;
    while (!glfwWindowShouldClose(mainWindow)) {
        // movement calculation
        if (addDelta) {
            moveOffset += moveDelta;
        } else {
            moveOffset -= moveDelta;
        }
        if (moveOffset >= maxMoveOffset || moveOffset <= -maxMoveOffset) addDelta = !addDelta;

        // rotation calculation
        rotationAngle += rotationAngleDelta;
        if (rotationAngle >= 360.f) {
            rotationAngle -= 360.f;
        }


        glfwPollEvents();

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
        model = glm::rotate(model, degreesToRadians(rotationAngle), glm::vec3(0.f, 1.f, 0.f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        for (std::unique_ptr<Mesh>& mesh : meshArray) {
            mesh->render();
        }

        glfwSwapBuffers(mainWindow);
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}
