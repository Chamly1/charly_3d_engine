#include "GLFWinputHandler.hpp"

void GLFWinputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;

    switch (action) {
        case GLFW_PRESS:
        case GLFW_REPEAT:
            inputEvent.type = InputEvent::KeyPressed;
            inputEvent.code = key;
            thisHandler->mInputEventQueue.push(InputEvent(inputEvent));
            break;
        case GLFW_RELEASE:
            inputEvent.type = InputEvent::KeyReleased;
            inputEvent.code = key;
            thisHandler->mInputEventQueue.push(InputEvent(inputEvent));
            break;
    }
}

void GLFWinputHandler::museButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;

    switch (action) {
        case GLFW_PRESS:
            inputEvent.type = InputEvent::KeyPressed;
            inputEvent.code = button;
            thisHandler->mInputEventQueue.push(InputEvent(inputEvent));
            break;
        case GLFW_RELEASE:
            inputEvent.type = InputEvent::KeyReleased;
            inputEvent.code = button;
            thisHandler->mInputEventQueue.push(InputEvent(inputEvent));
            break;
    }
}

GLFWinputHandler::GLFWinputHandler() {

}

GLFWinputHandler::GLFWinputHandler(GLFWwindow *window) {
    init(window);
}

GLFWinputHandler::~GLFWinputHandler() {

}

void GLFWinputHandler::init(GLFWwindow *window) {
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, museButtonCallback);
}

bool GLFWinputHandler::pullInputEvent(InputEvent& event) {
    if (!mInputEventQueue.empty()) {
        event = mInputEventQueue.front();
        mInputEventQueue.pop();
        return true;
    }
    return false;
}
