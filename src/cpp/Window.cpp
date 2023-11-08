#include "Window.hpp"
#include "Logger.hpp"
#include "OpenGLUtils.hpp"

namespace Charly {

    static const GLint DEFAULT_WINDOW_WIDTH = 800, DEFAULT_WINDOW_HEIGHT = 600;

    Window::Window()
    : mWindow(nullptr)
    , mWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT) {
        if (!glfwInit()) {
            LOG_ERROR("GLFW initialization failed!")
//        return 1;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // no backwards compatibility?
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        mWindow = glfwCreateWindow(mWindowSize.x, mWindowSize.y, "title", NULL, NULL);
        if (!mWindow) {
            LOG_ERROR("GLFW window creation failed!")
            glfwTerminate();
//        return 1;
        }

//        glfwGetFramebufferSize(mWindow, &mFramebufferWidth, &mFramebufferHeight);

        // set context for GLEW to use
        glfwMakeContextCurrent(mWindow);
        // disable V-sync
        glfwSwapInterval(0);

        glewExperimental = GL_TRUE;

        if (glewInit() != GLEW_OK) {
            LOG_ERROR("GLEW initialization failed!")
            glfwDestroyWindow(mWindow);
            glfwTerminate();
//        return 1;
        }

        GL_CALL(glEnable(GL_DEPTH_TEST))
        GL_CALL(glEnable(GL_BLEND))
        GL_CALL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA))
        // setup viewport size
        GL_CALL(glViewport(0, 0, mWindowSize.x, mWindowSize.y))
    }

    Window::~Window() {
        glfwDestroyWindow(mWindow);
        glfwTerminate();
    }

    bool Window::shouldClose() {
        if (glfwWindowShouldClose(mWindow) == 1) {
            return true;
        } else {
            return false;
        }
    }

    void Window::clear() {
        GL_CALL(glClearColor(0.f, 0.f, 0.f, 1.f))
        GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT))
    }

    void Window::swapBuffers() {
        glfwSwapBuffers(mWindow);
    }

    glm::ivec2 Window::getSize() {
        return mWindowSize;
    }

}
