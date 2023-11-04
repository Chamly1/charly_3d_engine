#include "OpenGLapp.hpp"
#include "utils.hpp"
#include "Font.hpp"
#include "Text.hpp"
#include "Logger.hpp"
#include "OpenGLUtils.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

// window size
static const GLint DEFAULT_WINDOW_WIDTH = 800, DEFAULT_WINDOW_HEIGHT = 600;

namespace Charly {

    void OpenGLapp::createAndSetupWindow() {
        if (!glfwInit()) {
            LOG_ERROR("GLFW initialization failed!")
//        return 1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // no backwards compatibility?
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        mWindow = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, "title", NULL, NULL);
        if (!mWindow) {
            LOG_ERROR("GLFW window creation failed!")
            glfwTerminate();
//        return 1;
        }

        glfwGetFramebufferSize(mWindow, &mFramebufferWidth, &mFramebufferHeight);

        // set context for GLEW to use
        glfwMakeContextCurrent(mWindow);

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) {
            LOG_ERROR("GLEW initialization failed!")
            glfwDestroyWindow(mWindow);
            glfwTerminate();
//        return 1;
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // setup viewport size
        glViewport(0, 0, mFramebufferWidth, mFramebufferHeight);
    }

    void OpenGLapp::createModels() {
        GLfloat cubeVertices[] = {
                -1.f, -1.f, -1.f,  0.0f,  0.0f, -1.0f,
                1.f, -1.f, -1.f,  0.0f,  0.0f, -1.0f,
                1.f,  1.f, -1.f,  0.0f,  0.0f, -1.0f,
                1.f,  1.f, -1.f,  0.0f,  0.0f, -1.0f,
                -1.f,  1.f, -1.f,  0.0f,  0.0f, -1.0f,
                -1.f, -1.f, -1.f,  0.0f,  0.0f, -1.0f,

                -1.f, -1.f,  1.f,  0.0f,  0.0f,  1.0f,
                1.f, -1.f,  1.f,  0.0f,  0.0f,  1.0f,
                1.f,  1.f,  1.f,  0.0f,  0.0f,  1.0f,
                1.f,  1.f,  1.f,  0.0f,  0.0f,  1.0f,
                -1.f,  1.f,  1.f,  0.0f,  0.0f,  1.0f,
                -1.f, -1.f,  1.f,  0.0f,  0.0f,  1.0f,

                -1.f,  1.f,  1.f, -1.0f,  0.0f,  0.0f,
                -1.f,  1.f, -1.f, -1.0f,  0.0f,  0.0f,
                -1.f, -1.f, -1.f, -1.0f,  0.0f,  0.0f,
                -1.f, -1.f, -1.f, -1.0f,  0.0f,  0.0f,
                -1.f, -1.f,  1.f, -1.0f,  0.0f,  0.0f,
                -1.f,  1.f,  1.f, -1.0f,  0.0f,  0.0f,

                1.f,  1.f,  1.f,  1.0f,  0.0f,  0.0f,
                1.f,  1.f, -1.f,  1.0f,  0.0f,  0.0f,
                1.f, -1.f, -1.f,  1.0f,  0.0f,  0.0f,
                1.f, -1.f, -1.f,  1.0f,  0.0f,  0.0f,
                1.f, -1.f,  1.f,  1.0f,  0.0f,  0.0f,
                1.f,  1.f,  1.f,  1.0f,  0.0f,  0.0f,

                -1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f,
                1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f,
                1.f, -1.f,  1.f,  0.0f, -1.0f,  0.0f,
                1.f, -1.f,  1.f,  0.0f, -1.0f,  0.0f,
                -1.f, -1.f,  1.f,  0.0f, -1.0f,  0.0f,
                -1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f,

                -1.f,  1.f, -1.f,  0.0f,  1.0f,  0.0f,
                1.f,  1.f, -1.f,  0.0f,  1.0f,  0.0f,
                1.f,  1.f,  1.f,  0.0f,  1.0f,  0.0f,
                1.f,  1.f,  1.f,  0.0f,  1.0f,  0.0f,
                -1.f,  1.f,  1.f,  0.0f,  1.0f,  0.0f,
                -1.f,  1.f, -1.f,  0.0f,  1.0f,  0.0f
        };

        BufferLayout cubeBufferLayout = {
                {ShaderDataType::Float3, "pos"},
                {ShaderDataType::Float3, "normal"}
        };
        std::shared_ptr<VertexBuffer> cubeVertexBuffer = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
        std::shared_ptr<VertexArray> cubeVertexArray = std::make_shared<VertexArray>(cubeVertexBuffer, cubeBufferLayout);

        std::shared_ptr<Shader> baseShader = std::make_shared<Shader>("resources/shaders/base_shader.vert",
                                                        "resources/shaders/base_shader.frag");

        std::shared_ptr<Material> material = std::make_shared<Material>();
        material->setColor(glm::vec4(0.2f, 0.3f, 0.8f, 1.f));

        mModel = std::make_shared<Model>(cubeVertexArray, baseShader, material);
        mModel->setPosition(glm::vec3(0.f, 0.f, 0.f));
    }

    void OpenGLapp::handleEvents() {
        glfwPollEvents();

        InputEvent event;
        while (mInputHandel.pullInputEvent(event)) {
            if (mInputHandel.isMouseButtonPressed(GLFW_MOUSE_BUTTON_3)) {

                if (event.type == InputEvent::InputEventType::MouseMoved) {

                    if (mInputHandel.isKeyPressed(GLFW_KEY_LEFT_SHIFT)) {
                        mCamera.changeRotationSphereCenterPosition(static_cast<float>(-event.moveEvent.moveDeltaX),
                                                                   static_cast<float>(event.moveEvent.moveDeltaY));
                    } else {
                        mCamera.rotateOnSphere(static_cast<float>(event.moveEvent.moveDeltaX),
                                               static_cast<float>(-event.moveEvent.moveDeltaY));
                    }

                }
            }

            if (event.type == InputEvent::InputEventType::MouseWheelScrolled) {
                mCamera.changeRotationSphereRadius(static_cast<float>(-event.scrollEvent.yoffset));
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

//        shaderNum = 5;
//        mShaderArray[shaderNum]->bind();
//        mShaderArray[shaderNum]->uploadUniformMatrix4f("u_Projection", mProjectionMatrixOrthographic);
//        mShaderArray[shaderNum]->uploadUniform3f("u_TextColor", glm::vec3(0.f, 1.f, 0.f));
//        Font font("resources/fonts/asd.TTF");
////        Font font("resources/fonts/CONSOLA.TTF");
//        Text text(font, "The quick brown fox jumps over the lazy dog\n11111111111111 .....", 15);
//        text.draw();

        mModel->draw(mCamera.calculateViewMatrix(), mProjectionMatrixPerspective);


        glUseProgram(0);
        glfwSwapBuffers(mWindow);
    }

    OpenGLapp::OpenGLapp()
            : mCamera(glm::vec3(0.f, 0.f, 2.5f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f) {
        createAndSetupWindow();
        createModels();

        mInputHandel.init(mWindow);

        GLfloat projectionAspectRation = static_cast<GLfloat>(mFramebufferWidth) / static_cast<GLfloat>(mFramebufferHeight);
        mProjectionMatrixPerspective = glm::perspective(45.f, projectionAspectRation, 0.1f, 100.f);
        mProjectionMatrixOrthographic = glm::ortho(0.0f, static_cast<float>(mFramebufferWidth), 0.0f, static_cast<float>(mFramebufferHeight));

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

}
