#include "Material.hpp"

namespace Charly {

    Material::Material()
    : mTexture(nullptr)
    , mColor(0.f) {

    }

    Material::Material(const std::shared_ptr<Texture>& texture)
    : mTexture(texture)
    , mColor(1.f, 0.f, 1.f) {

    }

    void Material::setColor(const glm::vec3& color) {
        mColor = color;
    }

    glm::vec3 Material::getColor() const {
        return mColor;
    }

    void Material::bind() const {
        if (mTexture != nullptr) {
            mTexture->bind();
        }
    }

}
