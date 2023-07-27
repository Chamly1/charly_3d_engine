#ifndef LEARN_OPENGL_GLFWINPUTHANDLER_HPP
#define LEARN_OPENGL_GLFWINPUTHANDLER_HPP

#include "GLFW/glfw3.h"

#include <queue>

struct InputEvent {
    enum InputEventType {
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
    };

    InputEventType type;
    int code;
};

class GLFWinputHandler {
private:
    std::queue<InputEvent> mInputEventQueue;

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void museButtonCallback(GLFWwindow* window, int button, int action, int mods);

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

    // delete implicit methods
    GLFWinputHandler(GLFWinputHandler const &) = delete;
    GLFWinputHandler & operator = (GLFWinputHandler const &) = delete;
    GLFWinputHandler(GLFWinputHandler &&) = delete;
    GLFWinputHandler & operator = (GLFWinputHandler &&) = delete;
};

#endif //LEARN_OPENGL_GLFWINPUTHANDLER_HPP
