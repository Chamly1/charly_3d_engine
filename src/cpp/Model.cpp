#include "Model.hpp"
#include "Renderer.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Charly {

    Model::Model()
    : mVertexArray(nullptr)
    , mShader(nullptr)
    , mMaterial(nullptr)
    , mPosition(0.f)
    , mRotation(1.f)
    , mScale(1.f) {

    }

    void Model::init(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material) {
        mVertexArray = vertexArray;
        mShader = shader;
        mMaterial = material;
    }

    void Model::setVertexArray(const std::shared_ptr<VertexArray>& vertexArray) {
        mVertexArray = vertexArray;
    }

    void Model::draw(Renderer& renderer) const {
        glm::mat4 model(1.f);
        model = glm::translate(model, mPosition);
        model = glm::rotate(model, glm::radians(360.f), mRotation);
        model = glm::scale(model, mScale);

        mMaterial->bind();

        mShader->bind();
        mShader->uploadUniformMatrix4f("u_Model", model);
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
    , mMaterial(material)
    , mPosition(0.f)
    , mRotation(1.f)
    , mScale(1.f) {

    }

    void Model::setPosition(const glm::vec3& position) {
        mPosition = position;
    }

}
