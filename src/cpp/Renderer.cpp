#include "Renderer.hpp"
#include "Drawable.hpp"

#include "glm/gtc/matrix_transform.hpp"

namespace Charly {

    Renderer::Renderer(const glm::ivec2&& windowSize)
    : mViewMatrix(1.f)
    , mCurrentProjectionMatrix(&mProjectionMatrixPerspective) {
        float projectionAspectRation = static_cast<float>(windowSize.x) / static_cast<float>(windowSize.y);
        mProjectionMatrixPerspective = glm::perspective(45.f, projectionAspectRation, 0.1f, 100.f);
        mProjectionMatrixOrthographic = glm::ortho(0.0f, static_cast<float>(windowSize.x), 0.0f, static_cast<float>(windowSize.y));
    }

    Renderer::~Renderer() {

    }

    void Renderer::setViewMatrix(glm::mat4 viewMatrix) {
        mViewMatrix = viewMatrix;
    }

    void Renderer::setProjectionMode(ProjectionMode projectionMode) {
        switch (projectionMode) {
            case ProjectionMode::Perspective:
                mCurrentProjectionMatrix = &mProjectionMatrixPerspective;
                break;
            case ProjectionMode::Orthographic:
                mCurrentProjectionMatrix = &mProjectionMatrixOrthographic;
                break;
        }
    }

    const glm::mat4& Renderer::getViewMatrix() const {
        return mViewMatrix;
    }

    const glm::mat4& Renderer::getProjectionMatrix() const {
        return *mCurrentProjectionMatrix;
    }

    void Renderer::draw(const Drawable& drawable) {
        drawable.draw(*this);
    }

}
