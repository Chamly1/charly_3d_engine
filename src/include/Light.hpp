#ifndef CHARLY_3D_ENGINE_LIGHT_HPP
#define CHARLY_3D_ENGINE_LIGHT_HPP

#include "glm/glm.hpp"

namespace Charly {

    struct PointLight {
        glm::vec3 color;
        glm::vec3 position;
    };

    struct AmbientLight {
        glm::vec3 color;
        float strength;
    };

}

#endif //CHARLY_3D_ENGINE_LIGHT_HPP
