#ifndef LEARN_OPENGL_CAMERA_HPP
#define LEARN_OPENGL_CAMERA_HPP

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class MoveDirection {
    Forward,
    Backward,
    Left,
    Right
};

class Camera {
private:
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    GLfloat mYaw;
    GLfloat mPitch;

    GLfloat mMoveSpeed;
    GLfloat mTurnSpeed;

    glm::vec3 mMoveDirection;

public:
    Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch);

    void update(float dt);
    void move(MoveDirection direction);
    glm::mat4 calculateViewMatrix();
};

#endif //LEARN_OPENGL_CAMERA_HPP
