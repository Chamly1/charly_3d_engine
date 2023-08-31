#ifndef LEARN_OPENGL_GLFWINPUTHANDLER_HPP
#define LEARN_OPENGL_GLFWINPUTHANDLER_HPP

#include "GLFW/glfw3.h"

#include <queue>

namespace Charly {

    struct InputEvent {
        enum InputEventType {
            KeyPressed,
            KeyReleased,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved, // data in .moveEvent
            MouseWheelScrolled // data in .scrollEvent
        };

        struct MouseMoveEvent {
            double posX;
            double posY;
            double moveDeltaX;
            double moveDeltaY;
        };

        struct MouseWheelScrollEvent {
            double xoffset;
            double yoffset;
        };

        InputEventType type;

        int code;
        MouseMoveEvent moveEvent;
        MouseWheelScrollEvent scrollEvent;
    };

    class GLFWinputHandler {
    private:
        std::queue<InputEvent> mInputEventQueue;

        bool mMouseFirstMove;
        double mMousePosX;
        double mMousePosY;

        bool mIsKeyOrButtonPressed[GLFW_KEY_LAST];

        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void museButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

    public:
        GLFWinputHandler();
        GLFWinputHandler(GLFWwindow *window);
        ~GLFWinputHandler();

        void init(GLFWwindow *window);
        /**
         * Pop the event on top of the event queue, if any, and return save it inside 'event' parameter.
         *
         * @param event poped event, if any
         * @return true if an event was returned
         */
        bool pullInputEvent(InputEvent& event);
        /**
         *
         * @param key use GLFW_KEY_
         * @return
         */
        bool isKeyPressed(int key);
        /**
         *
         * @param button use GLFW_MOUSE_BUTTON_
         * @return
         */
        bool isMouseButtonPressed(int button);

        // delete implicit methods
        GLFWinputHandler(GLFWinputHandler const &) = delete;
        GLFWinputHandler & operator = (GLFWinputHandler const &) = delete;
        GLFWinputHandler(GLFWinputHandler &&) = delete;
        GLFWinputHandler & operator = (GLFWinputHandler &&) = delete;
    };

}

#endif //LEARN_OPENGL_GLFWINPUTHANDLER_HPP
