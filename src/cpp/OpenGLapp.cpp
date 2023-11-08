#include "OpenGLapp.hpp"
#include "utils.hpp"
#include "Font.hpp"
#include "Text.hpp"
#include "Logger.hpp"
#include "OpenGLUtils.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

namespace Charly {

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

        ///////////////////text///////////////////

//        std::shared_ptr<Font> font = std::make_shared<Font>("resources/fonts/asd.TTF");
        std::shared_ptr<Font> font = std::make_shared<Font>("resources/fonts/CONSOLA.TTF");

        std::shared_ptr<Shader> textShader = std::make_shared<Shader>("resources/shaders/text.vert",
                                                                      "resources/shaders/text.frag");

        mText = std::make_shared<Text>(font, textShader, "The quick brown fox jumps over the lazy dog\n11111111111111 .....", 15);
        mText->setPosition(glm::vec3(0.f, 600.f, 0.f));

        ///////////////////PerformanceStatisticManager///////////////////

        mPerformanceStatisticManager = std::make_shared<PerformanceStatisticManager>(font, textShader);
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
        
    }
    void OpenGLapp::update(float dt) {
        mCamera.update(dt);
        mPerformanceStatisticManager->update(dt);
    }

    void OpenGLapp::render() {
        mWindow.clear();

        mModel->draw(mCamera.calculateViewMatrix(), mProjectionMatrixPerspective);
//        mText->draw(glm::mat4(1.f), mProjectionMatrixOrthographic);
        mPerformanceStatisticManager->draw(glm::mat4(1.f), mProjectionMatrixOrthographic);

        glUseProgram(0);
        mWindow.swapBuffers();
    }

    OpenGLapp::OpenGLapp()
            : mCamera(glm::vec3(0.f, 0.f, 2.5f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f) {

        createModels();

        mInputHandel.init(mWindow);

        glm::ivec2 windowSize = mWindow.getSize();
        GLfloat projectionAspectRation = static_cast<GLfloat>(windowSize.x) / static_cast<GLfloat>(windowSize.y);
        mProjectionMatrixPerspective = glm::perspective(45.f, projectionAspectRation, 0.1f, 100.f);
        mProjectionMatrixOrthographic = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y));

//    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

    OpenGLapp::~OpenGLapp() {

        mModel.reset();
        mText.reset();
        mPerformanceStatisticManager.reset();

        // you must destroy all members whose destructors calls OpenGL function, before destroying the window because
        // GL_CALL() macro call in destructor goes into infinite loop as a result of calling OpenGL functions without
        // valid OpenGL context!!!
    }

    void OpenGLapp::run() {
        float prevTime;
        float currTime = static_cast<float>(glfwGetTime());
        float deltaTime = 0.f;

        float performanceStatisticTime = 0.f;

        while (!mWindow.shouldClose()) {
            prevTime = currTime;
            currTime = static_cast<float>(glfwGetTime());
            deltaTime = currTime - prevTime;

            handleEvents();

            performanceStatisticTime = static_cast<float>(glfwGetTime());
            update(deltaTime);
            mPerformanceStatisticManager->accumulateUpdateTime(static_cast<float>(glfwGetTime()) - performanceStatisticTime);
            mPerformanceStatisticManager->incrementLogicUpdatesCounter();

            performanceStatisticTime = static_cast<float>(glfwGetTime());
            render();
            mPerformanceStatisticManager->accumulateRenderTime(static_cast<float>(glfwGetTime()) - performanceStatisticTime);
            mPerformanceStatisticManager->incrementFramesCounter();
        }
    }

}
