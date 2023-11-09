#include "Model.hpp"
#include "Renderer.hpp"

namespace Charly {

    void Model::draw(Renderer& renderer) const {
        mMaterial->bind();

        mShader->bind();
        mShader->uploadUniformMatrix4f("u_Model", calculateModelMatrix());
        mShader->uploadUniformMatrix4f("u_Projection", renderer.getProjectionMatrix());
        mShader->uploadUniformMatrix4f("u_View", renderer.getViewMatrix());

        mShader->uploadUniform3f("u_Color", mMaterial->getColor());
        mShader->uploadUniform3f("u_LightColor", renderer.getLightSource().mColor);
        mShader->uploadUniform3f("u_LightPos", renderer.getLightSource().mPosition);

        mVertexArray->draw();
    }

    Model::Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material)
    : mVertexArray(vertexArray)
    , mShader(shader)
    , mMaterial(material) {

    }

}
