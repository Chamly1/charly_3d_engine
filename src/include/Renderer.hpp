#ifndef CHARLY_3D_ENGINE_RENDERER_HPP
#define CHARLY_3D_ENGINE_RENDERER_HPP

#include "Light.hpp"

#include "glm/glm.hpp"

namespace Charly {

    class Drawable;

    enum class ProjectionMode {
        Perspective,
        Orthographic
    };

    class Renderer {
    private:
        glm::mat4 mViewMatrix;
        glm::mat4* mCurrentProjectionMatrix;
        PointLight mPointLight;
        AmbientLight mAmbientLight;

        glm::mat4 mProjectionMatrixPerspective;
        glm::mat4 mProjectionMatrixOrthographic;

    public:
        Renderer(const glm::ivec2&& windowSize);
        ~Renderer();

        void setViewMatrix(glm::mat4 viewMatrix);
        void setProjectionMode(ProjectionMode projectionMode);
        void setPointLight(PointLight pointLight);
        void setAmbientLight(AmbientLight ambientLight);

        const glm::mat4& getViewMatrix() const;
        const glm::mat4& getProjectionMatrix() const;
        const PointLight& getPointLight() const;
        const AmbientLight& getAmbientLight() const;

        void draw(const Drawable& drawable);

    };

}

#endif //CHARLY_3D_ENGINE_RENDERER_HPP
