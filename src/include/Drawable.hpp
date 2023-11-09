#ifndef CHARLY_3D_ENGINE_RENDERABLE_HPP
#define CHARLY_3D_ENGINE_RENDERABLE_HPP

#include "glm/glm.hpp"

namespace Charly {

    class Renderer;

    class Drawable {
    protected:
        virtual void draw(Renderer& renderer) const = 0;

        friend Renderer;
    };

}

#endif //CHARLY_3D_ENGINE_RENDERABLE_HPP
