#ifndef CHARLY_3D_ENGINE_MATERIAL_HPP
#define CHARLY_3D_ENGINE_MATERIAL_HPP

#include "Shader.hpp"

namespace Charly {

    class Material {
    private:
        Shader mShader;
        glm::vec3 mColor;

    public:
        Material(const char* vertexShaderPath, const char* fragmentShaderPath);

        void bind() const;
        void unbind() const;

        // delete implicit methods
        Material(Material const &) = delete;
        Material & operator = (Material const &) = delete;
        Material(Material &&) = delete;
        Material & operator = (Material &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_MATERIAL_HPP
