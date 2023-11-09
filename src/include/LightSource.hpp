#ifndef CHARLY_3D_ENGINE_LIGHTSOURCE_HPP
#define CHARLY_3D_ENGINE_LIGHTSOURCE_HPP

#include "glm/glm.hpp"

namespace Charly {

    class LightSource {
    public:
        glm::vec3 mColor;
        glm::vec3 mPosition;
    };

}

#endif //CHARLY_3D_ENGINE_LIGHTSOURCE_HPP
