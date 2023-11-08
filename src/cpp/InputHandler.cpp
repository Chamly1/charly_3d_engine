#include "InputHandler.hpp"

namespace Charly {

    void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        InputHandler* thisHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

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

    void InputHandler::museButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        InputHandler* thisHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

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

    void InputHandler::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
        InputHandler* thisHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

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

    void InputHandler::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        InputHandler* thisHandler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));

        InputEvent inputEvent;
        inputEvent.type = InputEvent::MouseWheelScrolled;

        inputEvent.scrollEvent.xoffset = xoffset;
        inputEvent.scrollEvent.yoffset = yoffset;
        thisHandler->mInputEventQueue.push(inputEvent);
    }

    InputHandler::InputHandler() {

    }

    InputHandler::InputHandler(Window& window) {
        init(window);
    }

    InputHandler::~InputHandler() {

    }

    void InputHandler::init(Window& window) {
        glfwSetWindowUserPointer(window.mWindow, this);
        memset(mIsKeyOrButtonPressed, 0, sizeof(mIsKeyOrButtonPressed));

        glfwSetKeyCallback(window.mWindow, keyCallback);
        glfwSetMouseButtonCallback(window.mWindow, museButtonCallback);
        mMouseFirstMove = true;
        mMousePosX = 0.f;
        mMousePosY = 0.f;
        glfwSetCursorPosCallback(window.mWindow, cursorPosCallback);
        glfwSetScrollCallback(window.mWindow, scrollCallback);
    }

    bool InputHandler::pullInputEvent(InputEvent& event) {
        if (!mInputEventQueue.empty()) {
            event = mInputEventQueue.front();
            mInputEventQueue.pop();
            return true;
        }
        return false;
    }

    bool InputHandler::isKeyPressed(int key) {
        return mIsKeyOrButtonPressed[key];
    }

    bool InputHandler::isMouseButtonPressed(int button) {
        return mIsKeyOrButtonPressed[button];
    }

}
