#include "OpenGLapp.hpp"
#include "utils.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

// window size
static const GLint DEFAULT_WINDOW_WIDTH = 800, DEFAULT_WINDOW_HEIGHT = 600;

namespace Charly {

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

    void OpenGLapp::createVertexArrays() {
        unsigned int pyramidIndices[] = {
                0, 3, 1,
                1, 3, 2,
                2, 3, 0,
                0, 1, 2
        };

        GLfloat pyramidVertices[] = {
                -1.f, -1.f, 0.f, 0.f, 0.f,
                0.f, -1.f, 1.f, 0.5f, 0.f,
                1.f, -1.f, 0.f, 1.f, 0.f,
                0.f, 1.f, 0.f, 0.5f, 1.f
        };

        BufferLayout pyramidBufferLayout = {
                {ShaderDataType::Float3, "pos"},
                {ShaderDataType::Float2, "tex"}
        };
        std::shared_ptr<VertexBuffer> pyramidVertexBuffer = std::make_shared<VertexBuffer>(pyramidVertices, sizeof(pyramidVertices) * sizeof(float), pyramidBufferLayout);
        std::shared_ptr<IndexBuffer> pyramidIndexBuffer = std::make_shared<IndexBuffer>(pyramidIndices, sizeof(pyramidIndices) / sizeof(unsigned int));
        mVertexArrays.push_back(std::make_unique<VertexArray>(pyramidVertexBuffer, pyramidIndexBuffer));

        unsigned int cubeIndices[] = {
                0, 1, 3, 3, 1, 2,
                1, 5, 2, 2, 5, 6,
                5, 4, 6, 6, 4, 7,
                4, 0, 7, 7, 0, 3,
                3, 2, 7, 7, 2, 6,
                4, 5, 0, 0, 5, 1
        };

        GLfloat cubeVertices[] = {
                -1.f, -1.f, -1.f,
                1.f, -1.f, -1.f,
                1.f, 1.f, -1.f,
                -1.f, 1.f, -1.f,

                -1.f, -1.f, 1.f,
                1.f, -1.f, 1.f,
                1.f, 1.f, 1.f,
                -1.f, 1.f, 1.f
        };

        BufferLayout cubeBufferLayout = {
                {ShaderDataType::Float3, "pos"}
        };
        std::shared_ptr<VertexBuffer> cubeVertexBuffer = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices) * sizeof(float), cubeBufferLayout);
        std::shared_ptr<IndexBuffer> cubeIndexBuffer = std::make_shared<IndexBuffer>(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
        mVertexArrays.push_back(std::make_unique<VertexArray>(cubeVertexBuffer, cubeIndexBuffer));
    }

    void OpenGLapp::createShaders() {
        mShaderArray.push_back(std::make_unique<Shader>("resources/shaders/base_shader.vert",
                                                        "resources/shaders/base_shader.frag"));
        mShaderArray.push_back(std::make_unique<Shader>("resources/shaders/texturing.vert",
                                                        "resources/shaders/texturing.frag"));
        mShaderArray.push_back(std::make_unique<Shader>("resources/shaders/flat_color.vert",
                                                        "resources/shaders/flat_color.frag"));
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

        // draw pyramid
        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
        model = glm::rotate(model, degreesToRadians(0), glm::vec3(0.f, 1.f, 0.f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        int shaderNum = 2;
        mShaderArray[shaderNum]->bind();
        mShaderArray[shaderNum]->uploadUniformMatrix4f("model", model);
        mShaderArray[shaderNum]->uploadUniformMatrix4f("projection", mProjectionMatrix);
        mShaderArray[shaderNum]->uploadUniformMatrix4f("view", mCamera.calculateViewMatrix());
        mShaderArray[shaderNum]->uploadUniform4f("uColor", glm::vec4(0.2f, 0.3f, 0.8f, 1.f));

        mTextureArray[0]->useTexture();
        mVertexArrays[0]->bind();
        glDrawElements(GL_TRIANGLES, mVertexArrays[0]->getIndicesCount(), GL_UNSIGNED_INT, 0);
        mVertexArrays[0]->unbind();

        // draw cube
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(2.f, 0.f, 0.f));
        model = glm::rotate(model, degreesToRadians(0), glm::vec3(0.f, 1.f, 0.f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));

        shaderNum = 2;
        mShaderArray[shaderNum]->bind();
        mShaderArray[shaderNum]->uploadUniformMatrix4f("model", model);
        mShaderArray[shaderNum]->uploadUniformMatrix4f("projection", mProjectionMatrix);
        mShaderArray[shaderNum]->uploadUniformMatrix4f("view", mCamera.calculateViewMatrix());
        mShaderArray[shaderNum]->uploadUniform4f("uColor", glm::vec4(0.2f, 0.3f, 0.8f, 1.f));

        mVertexArrays[1]->bind();
        glDrawElements(GL_TRIANGLES, mVertexArrays[1]->getIndicesCount(), GL_UNSIGNED_INT, 0);
        mVertexArrays[1]->unbind();

        glUseProgram(0);
        glfwSwapBuffers(mWindow);
    }

    OpenGLapp::OpenGLapp()
            : mCamera(glm::vec3(0.f, 0.f, 2.5f), glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f) {
        createAndSetupWindow();
        createVertexArrays();
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

}
