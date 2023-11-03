#include "Material.hpp"

namespace Charly {

    Material::Material(const std::shared_ptr<Texture>& texture)
    : mTexture(texture)
    , mColor(0.f) {

    }

    void Material::setColor(const glm::vec3& color) {
        mColor = color;
    }

    glm::vec3 Material::getColor() const {
        return mColor;
    }

    void Material::bind() const {
        mTexture->bind();
    }

}
