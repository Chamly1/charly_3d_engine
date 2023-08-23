#include "OpenGLapp.hpp"
#include "utils.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

// window size
static const GLint DEFAULT_WINDOW_WIDTH = 800, DEFAULT_WINDOW_HEIGHT = 600;

void OpenGLapp::createAndSetupWindow() {
    if (!glfwInit()) {
        std::cout << "GLFW initialization failed!\n";
//        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // no backwards compatibility?
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mWindow = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "title", NULL, NULL);
    if (!mWindow) {
        std::cout << "GLFW window creation failed!\n";
        glfwTerminate();
//        return 1;
    }

    glfwGetFramebufferSize(mWindow, &mFramebufferWidth, &mFramebufferHeight);

    // set context for GLEW to use
    glfwMakeContextCurrent(mWindow);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!\n";
        glfwDestroyWindow(mWindow);
        glfwTerminate();
//        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    // setup viewport size
    glViewport(0, 0, mFramebufferWidth, mFramebufferHeight);
}

void OpenGLapp::createMeshes() {
    unsigned int indices[] = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    GLfloat vertices[] = {
            -1.f, -1.f, 0.f, 0.f, 0.f,
            0.f, -1.f, 1.f, 0.5f, 0.f,
            1.f, -1.f, 0.f, 1.f, 0.f,
            0.f, 1.f, 0.f, 0.5f, 1.f
    };

    mMeshArray.push_back(std::make_unique<Mesh>(vertices, 20, indices, 12, true));
}

void OpenGLapp::createShaders() {
    mShaderArray.push_back(std::make_unique<Shader>("resources/shaders/base_shader.vert",
                                                    "resources/shaders/base_shader.frag"));
    mShaderArray.push_back(std::make_unique<Shader>("resources/shaders/texturing.vert",
                                                    "resources/shaders/texturing.frag"));
}

void OpenGLapp::createTextures() {
    mTextureArray.push_back(std::make_unique<Texture>("resources/textures/stone_texture.jpg", false));
}

void OpenGLapp::handleEvents() {
    glfwPollEvents();

    InputEvent event;
    while (mInputHandel.pullInputEvent(event)) {
        if (mInputHandel.isMouseButtonPressed(GLFW_MOUSE_BUTTON_3)) {
            if (event.type == InputEvent::InputEventType::MouseMoved) {
                mCamera.rotateOnSphere(static_cast<float>(event.moveEvent.moveDeltaX),
                                       static_cast<float>(-event.moveEvent.moveDeltaY));
            }
        }
    }

    // camera movement
    if (mInputHandel.isKeyPressed(GLFW_KEY_W)) {
        mCamera.move(MoveDirection::Forward);
    }
    if (mInputHandel.isKeyPressed(GLFW_KEY_S)) {
        mCamera.move(MoveDirection::Backward);
    }
    if (mInputHandel.isKeyPressed(GLFW_KEY_A)) {
        mCamera.move(MoveDirection::Left);
    }
    if (mInputHandel.isKeyPressed(GLFW_KEY_D)) {
        mCamera.move(MoveDirection::Right);
    }
}
void OpenGLapp::update(float dt) {
    mCamera.update(dt);
}

void OpenGLapp::render() {
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int shaderNum = 0;
    mShaderArray[shaderNum]->useShader();
    GLuint uniformModel = mShaderArray[shaderNum]->getUniformModel();
    GLuint uniformProjection = mShaderArray[shaderNum]->getUniformProjection();
    GLuint uniformView = mShaderArray[shaderNum]->getUniformView();

    glm::mat4 model(1.f);
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::rotate(model, degreesToRadians(0), glm::vec3(0.f, 1.f, 0.f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(mProjectionMatrix));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mCamera.calculateViewMatrix()));

    mTextureArray[0]->useTexture();
    for (std::unique_ptr<Mesh>& mesh : mMeshArray) {
        mesh->render();
    }

    glUseProgram(0);
    glfwSwapBuffers(mWindow);
}

OpenGLapp::OpenGLapp()
: mCamera(glm::vec3(0.f, 0.f, 2.5f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f) {
    createAndSetupWindow();
    createMeshes();
    createShaders();
    createTextures();

    mInputHandel.init(mWindow);

    GLfloat projectionAspectRation = static_cast<GLfloat>(mFramebufferWidth) / static_cast<GLfloat>(mFramebufferHeight);
    mProjectionMatrix = glm::perspective(45.f, projectionAspectRation, 0.1f, 100.f);

//    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

OpenGLapp::~OpenGLapp() {
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void OpenGLapp::run() {
    float prevTime;
    float currTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0.f;

    while (!glfwWindowShouldClose(mWindow)) {
        prevTime = currTime;
        currTime = static_cast<float>(glfwGetTime());
        deltaTime = currTime - prevTime;

        handleEvents();
        update(deltaTime);
        render();
    }
}
