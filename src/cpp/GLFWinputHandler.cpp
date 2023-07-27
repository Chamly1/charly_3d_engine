#include "GLFWinputHandler.hpp"

#include <iostream>

void GLFWinputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    GLFWinputHandler* thisHandler = static_cast<GLFWinputHandler*>(glfwGetWindowUserPointer(window));

    InputEvent inputEvent;

    switch (action) {
        case GLFW_PRESS:
        case GLFW_REPEAT:
            inputEvent.type = InputEvent::KeyPressed;
            inputEvent.code = key;
            thisHandler->mInputEventQueue.push(inputEvent);
            break;
        case GLFW_RELEASE:
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
            inputEvent.type = InputEvent::MouseButtonPressed;
            inputEvent.code = button;
            thisHandler->mInputEventQueue.push(inputEvent);
            break;
        case GLFW_RELEASE:
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
    mMouseFirstMove = true;
    mMousePosX = 0.f;
    mMousePosY = 0.f;
    glfwSetCursorPosCallback(window, cursorPosCallback);
}

bool GLFWinputHandler::pullInputEvent(InputEvent& event) {
    if (!mInputEventQueue.empty()) {
        event = mInputEventQueue.front();
        mInputEventQueue.pop();
        return true;
    }
    return false;
}
