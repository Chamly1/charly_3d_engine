#include "Model.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"
#include "ModelLoader.hpp"

namespace Charly {

    void Model::draw(Renderer& renderer) const {
        mMaterial->bind();

        mShader->bind();
        mShader->uploadUniformMatrix4f("u_Model", calculateModelMatrix());
        mShader->uploadUniformMatrix4f("u_Projection", renderer.getProjectionMatrix());
        mShader->uploadUniformMatrix4f("u_View", renderer.getViewMatrix());
        mShader->uploadUniformMatrix4f("u_NormalRotation", calculateRotationMatrix());

        mShader->uploadUniform3f("u_Color", mMaterial->getColor());
        mShader->uploadUniform3f("u_LightColor", renderer.getPointLight().color);
        mShader->uploadUniform3f("u_LightPos", renderer.getPointLight().position);
        mShader->uploadUniform3f("u_AmbientLightColor", renderer.getAmbientLight().color);
        mShader->uploadUniform1f("u_AmbientLightStrength", renderer.getAmbientLight().strength);

        mVertexArray->draw();
    }

    Model::Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material)
    : mVertexArray(vertexArray)
    , mShader(shader)
    , mMaterial(material) {

    }

    Model::Model(const char* modelPath, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material)
    : mVertexArray(ModelLoader::loadVertexArray(modelPath))
    , mShader(shader)
    , mMaterial(material) {

    }

}
