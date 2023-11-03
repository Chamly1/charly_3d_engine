#ifndef CHARLY_3D_ENGINE_MATERIAL_HPP
#define CHARLY_3D_ENGINE_MATERIAL_HPP

#include "Texture.hpp"

#include "glm/glm.hpp"

#include <memory>

namespace Charly {

    class Material {
    private:
        std::shared_ptr<Texture> mTexture;
        glm::vec3 mColor;

    public:
        Material(const std::shared_ptr<Texture>& texture);

        void setColor(const glm::vec3& color);
        glm::vec3 getColor() const;

        void bind() const;

        // delete implicit methods
        Material(Material const &) = delete;
        Material & operator = (Material const &) = delete;
        Material(Material &&) = delete;
        Material & operator = (Material &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_MATERIAL_HPP
