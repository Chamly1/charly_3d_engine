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
        mShader->uploadUniformMatrix4f("model", model);
        mShader->uploadUniformMatrix4f("projection", renderer.getProjectionMatrix());
        mShader->uploadUniformMatrix4f("view", renderer.getViewMatrix());
        mShader->uploadUniform3f("uColor", mMaterial->getColor());

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
