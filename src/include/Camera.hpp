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
    glm::vec3 mPosition; // camera position
    glm::vec3 mFront; // camera look direction vector
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;

    GLfloat mYaw;
    GLfloat mPitch;

    GLfloat mRotationSphereRadius;
    glm::vec3 mRotationSphereCenter;

    glm::vec3 mMoveDirection;

    void updateCameraPosition();

public:
    Camera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch);

    void update(float dt);
    void move(MoveDirection direction);
    void rotate(GLfloat xChange, GLfloat yChange);

    void rotateOnSphere(GLfloat xChange, GLfloat yChange);
    void changeRotationSphereRadius(GLfloat delta);
    void changeRotationSphereCenterPosition(GLfloat xChange, GLfloat yChange);

    glm::mat4 calculateViewMatrix();
};

#endif //LEARN_OPENGL_CAMERA_HPP
