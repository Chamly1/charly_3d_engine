#ifndef CHARLY_3D_ENGINE_MODEL_HPP
#define CHARLY_3D_ENGINE_MODEL_HPP

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Material.hpp"

namespace Charly {

    class Model {
    private:
        std::shared_ptr<VertexArray> mVAO;
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<Material> mMaterial;
        glm::vec3 mPosition;
        glm::vec3 mRotation;
        glm::vec3 mScale;

    public:
        Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material);

        void setPosition(const glm::vec3& position);

        void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const;

        // delete implicit methods
        Model(Model const &) = delete;
        Model & operator = (Model const &) = delete;
        Model(Model &&) = delete;
        Model & operator = (Model &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_MODEL_HPP
