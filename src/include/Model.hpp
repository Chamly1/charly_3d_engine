#ifndef CHARLY_3D_ENGINE_MODEL_HPP
#define CHARLY_3D_ENGINE_MODEL_HPP

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Drawable.hpp"

namespace Charly {

    class Model : public Drawable {
    private:
        std::shared_ptr<VertexArray> mVertexArray;
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<Material> mMaterial;
        glm::vec3 mPosition;
        glm::vec3 mRotation;
        glm::vec3 mScale;

    protected:
        Model();
        void init(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material);
        void setVertexArray(const std::shared_ptr<VertexArray>& vertexArray);

        void draw(Renderer& renderer) const override;

    public:
        Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material);

        void setPosition(const glm::vec3& position);

        // delete implicit methods
        Model(Model const &) = delete;
        Model & operator = (Model const &) = delete;
        Model(Model &&) = delete;
        Model & operator = (Model &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_MODEL_HPP
