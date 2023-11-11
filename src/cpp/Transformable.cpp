#include "Transformable.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Charly {

    Transformable::Transformable()
    : mPosition(0.f)
    , mRotation(1.f)
    , mScale(1.f) {

    }

    void Transformable::setPosition(const glm::vec3& position) {
        mPosition = position;
    }

    glm::mat4 Transformable::calculateModelMatrix() const {
        glm::mat4 model(1.f);
        model = glm::translate(model, mPosition);
        model = glm::rotate(model, glm::radians(360.f), mRotation);
        model = glm::scale(model, mScale);
        return model;
    }

    glm::mat4 Transformable::calculateRotationMatrix() const {
        glm::mat4 rotationMatrix(1.f);
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(360.f), mRotation);
        return rotationMatrix;
    }

}
