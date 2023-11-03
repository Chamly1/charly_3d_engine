#include "Model.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Charly {

    Model::Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material)
    : mVAO(vertexArray)
    , mShader(shader)
    , mMaterial(material)
    , mPosition(0.f)
    , mRotation(0.f)
    , mScale(1.f) {

    }

    void Model::setPosition(const glm::vec3& position) {
        mPosition = position;
    }

    void Model::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) const {
        glm::mat4 model(1.f);
        model = glm::translate(model, mPosition);
        model = glm::rotate(model, glm::radians(360.f), mRotation);
        model = glm::scale(model, mScale);

        mMaterial->bind();

        mShader->bind();
        mShader->uploadUniformMatrix4f("model", model);
        mShader->uploadUniformMatrix4f("projection", projectionMatrix);
        mShader->uploadUniformMatrix4f("view", viewMatrix);
        mShader->uploadUniform3f("uColor", mMaterial->getColor());

        mVAO->draw();
    }

}
