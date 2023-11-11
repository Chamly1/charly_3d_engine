#ifndef CHARLY_3D_ENGINE_TRANSFORMABLE_HPP
#define CHARLY_3D_ENGINE_TRANSFORMABLE_HPP

#include "glm/glm.hpp"

namespace Charly {

    class Transformable {
    private:
        glm::vec3 mPosition;
        glm::vec3 mRotation;
        glm::vec3 mScale;

    public:
        Transformable();

        void setPosition(const glm::vec3& position);

        glm::mat4 calculateModelMatrix() const;
        glm::mat4 calculateRotationMatrix() const;

    };

}

#endif //CHARLY_3D_ENGINE_TRANSFORMABLE_HPP
