#include "Camera.hpp"

static const float ROTATION_SPEED = 0.4f;
static const float SCROLL_SPEED = 0.1f;
static const float MOVE_SPEED = 2.5f;

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch)
: mPosition(position)
, mWorldUp(worldUp)
, mYaw(yaw)
, mPitch(pitch)
, mRotationSphereRadius(2.5f)
, mFront(0.f, 0.f, -1.f)
, mMoveDirection(0.f) {

}

void Camera::update(float dt) {
    // update rotation
    mFront.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront.y = sin(glm::radians(mPitch));
    mFront.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
    mFront = glm::normalize(mFront);

    mRight = glm::normalize(glm::cross(mFront, mWorldUp));
    mUp = glm::normalize(glm::cross(mRight, mFront));

    // update movement
    if (mMoveDirection.x != 0.f ||
        mMoveDirection.y != 0.f ||
        mMoveDirection.z != 0.f) {

        mMoveDirection = glm::normalize(mMoveDirection);
        mPosition += mMoveDirection * MOVE_SPEED * dt;
        mMoveDirection = glm::vec3(0.f);
    }

}

void Camera::move(MoveDirection direction) {
    switch(direction) {
        case MoveDirection::Forward:
            mMoveDirection += mFront;
            break;
        case MoveDirection::Backward:
            mMoveDirection -= mFront;
            break;
        case MoveDirection::Left:
            mMoveDirection -= mRight;
            break;
        case MoveDirection::Right:
            mMoveDirection += mRight;
            break;
    }
}

void Camera::rotate(GLfloat xChange, GLfloat yChange) {
    mYaw += xChange * ROTATION_SPEED;
    mPitch += yChange * ROTATION_SPEED;

    if (mPitch > 89.f) {
        mPitch = 89.f;
    } else if (mPitch < -89.f) {
        mPitch = -89.f;
    }
}

void Camera::updateCameraPosition() {
    mPosition.x = -mRotationSphereRadius * cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
    mPosition.y = -mRotationSphereRadius * sin(glm::radians(mPitch));
    mPosition.z = -mRotationSphereRadius * cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
}

void Camera::rotateOnSphere(GLfloat xChange, GLfloat yChange) {
    mYaw += xChange * ROTATION_SPEED;
    mPitch += yChange * ROTATION_SPEED;

    if (mPitch > 89.9f) {
        mPitch = 89.9f;
    } else if (mPitch < -89.9f) {
        mPitch = -89.9f;
    }

    updateCameraPosition();
}

void Camera::changeRotationSphereRadius(GLfloat delta) {
    mRotationSphereRadius += delta * SCROLL_SPEED;

    updateCameraPosition();
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mWorldUp);
}
