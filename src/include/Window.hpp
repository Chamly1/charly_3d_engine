#ifndef CHARLY_3D_ENGINE_WINDOW_HPP
#define CHARLY_3D_ENGINE_WINDOW_HPP

#include "gl/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace Charly {

    class InputHandler;

    class Window {
    private:
        GLFWwindow *mWindow;
        glm::ivec2 mWindowSize;

    public:
        Window(const glm::ivec2&& windowSize);
        ~Window();

        bool shouldClose();
        void clear();
        void swapBuffers();

        glm::ivec2 getSize();

        friend InputHandler;
    };

}

#endif //CHARLY_3D_ENGINE_WINDOW_HPP
