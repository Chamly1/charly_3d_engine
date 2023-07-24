#include "Mesh.hpp"
#include "Shader.hpp"

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
std::vector<std::unique_ptr<Shader>> shaderArray;

void createMeshes() {

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

void createShaders() {
    shaderArray.push_back(std::make_unique<Shader>("resources/shaders/base_shader.vert", "resources/shaders/base_shader.frag"));
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

    createMeshes();
    createShaders();

    GLuint uniformModel, uniformProjection;
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

        shaderArray[0]->useShader();
        uniformModel = shaderArray[0]->getUniformModel();
        uniformProjection = shaderArray[0]->getUniformProjection();

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.f, -2.5f));
        model = glm::rotate(model, degreesToRadians(rotationAngle), glm::vec3(0.f, 1.f, 0.f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        for (std::unique_ptr<Mesh>& mesh : meshArray) {
            mesh->render();
        }

        glUseProgram(0);

        glfwSwapBuffers(mainWindow);
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();

    return 0;
}
