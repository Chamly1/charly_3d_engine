#include "Material.hpp"

namespace Charly {

    Material::Material(const char* vertexShaderPath, const char* fragmentShaderPath)
    : mShader(vertexShaderPath, fragmentShaderPath)
    , mColor(0.f) {

    }

    void Material::bind() const {
        mShader.bind();
    }

    void Material::unbind() const {
        mShader.unbind();
    }

}
