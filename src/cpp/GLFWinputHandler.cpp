#include "GLFWinputHandler.hpp"

void GLFWinputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;

    switch (action) {
        case GLFW_PRESS:
        case GLFW_REPEAT:
            thisHandler->mIsKeyOrButtonPressed[key] = true;

            inputEvent.type = InputEvent::KeyPressed;
            inputEvent.code = key;
            thisHandler->mInputEventQueue.push(inputEvent);
            break;
        case GLFW_RELEASE:
            thisHandler->mIsKeyOrButtonPressed[key] = false;

            inputEvent.type = InputEvent::KeyReleased;
            inputEvent.code = key;
            thisHandler->mInputEventQueue.push(inputEvent);
            break;
    }
}

void GLFWinputHandler::museButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;

    switch (action) {
        case GLFW_PRESS:
            thisHandler->mIsKeyOrButtonPressed[button] = true;

            inputEvent.type = InputEvent::MouseButtonPressed;
            inputEvent.code = button;
            thisHandler->mInputEventQueue.push(inputEvent);
            break;
        case GLFW_RELEASE:
            thisHandler->mIsKeyOrButtonPressed[button] = false;

            inputEvent.type = InputEvent::MouseButtonReleased;
            inputEvent.code = button;
            thisHandler->mInputEventQueue.push(inputEvent);
            break;
    }
}

void GLFWinputHandler::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;
    inputEvent.type = InputEvent::MouseMoved;

    if (thisHandler->mMouseFirstMove) {
        thisHandler->mMouseFirstMove = false;
    } else {
        inputEvent.moveEvent.posX = xpos;
        inputEvent.moveEvent.posY = ypos;
        inputEvent.moveEvent.moveDeltaX = xpos - thisHandler->mMousePosX;
        inputEvent.moveEvent.moveDeltaY = ypos - thisHandler->mMousePosY;
        thisHandler->mInputEventQueue.push(inputEvent);
    }

    thisHandler->mMousePosX = xpos;
    thisHandler->mMousePosY = ypos;
}

void GLFWinputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;
    inputEvent.type = InputEvent::MouseWheelScrolled;

    inputEvent.scrollEvent.xoffset = xoffset;
    inputEvent.scrollEvent.yoffset = yoffset;
    thisHandler->mInputEventQueue.push(inputEvent);
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
    memset(mIsKeyOrButtonPressed, 0, sizeof(mIsKeyOrButtonPressed));

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, museButtonCallback);
    mMouseFirstMove = true;
    mMousePosX = 0.f;
    mMousePosY = 0.f;
    glfwSetCursorPosCallback(window, cursorPosCallback);
    glfwSetScrollCallback(window, scrollCallback);
}

bool GLFWinputHandler::pullInputEvent(InputEvent& event) {
    if (!mInputEventQueue.empty()) {
        event = mInputEventQueue.front();
        mInputEventQueue.pop();
        return true;
    }
    return false;
}

bool GLFWinputHandler::isKeyPressed(int key) {
    return mIsKeyOrButtonPressed[key];
}

bool GLFWinputHandler::isMouseButtonPressed(int button) {
    return mIsKeyOrButtonPressed[button];
}
