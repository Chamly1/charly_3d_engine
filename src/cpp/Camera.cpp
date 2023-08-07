#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch)
: mPosition(position)
, mWorldUp(worldUp)
, mYaw(yaw)
, mPitch(pitch)
, mRotationSphereRadius(2.5f)
, mFront(0.f, 0.f, -1.f)
, mMoveSpeed(2.5f)
, mTurnSpeed(0.4f)
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
        mPosition += mMoveDirection * mMoveSpeed * dt;
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
    mYaw += xChange * mTurnSpeed;
    mPitch += yChange * mTurnSpeed;

    if (mPitch > 89.f) {
        mPitch = 89.f;
    } else if (mPitch < -89.f) {
        mPitch = -89.f;
    }
}

void Camera::rotateOnSphere(GLfloat xChange, GLfloat yChange) {
    mYaw += xChange * mTurnSpeed;
    mPitch += yChange * mTurnSpeed;

    if (mPitch > 89.9f) {
        mPitch = 89.9f;
    } else if (mPitch < -89.9f) {
        mPitch = -89.9f;
    }

    mPosition.x = -mRotationSphereRadius * cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
    mPosition.y = -mRotationSphereRadius * sin(glm::radians(mPitch));
    mPosition.z = -mRotationSphereRadius * cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
}

glm::mat4 Camera::calculateViewMatrix() {
    return glm::lookAt(mPosition, mPosition + mFront, mWorldUp);
}
