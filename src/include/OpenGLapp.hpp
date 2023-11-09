#ifndef CHAMLY_3D_ENGINE_OPENGLAPP_HPP
#define CHAMLY_3D_ENGINE_OPENGLAPP_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "InputHandler.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Model.hpp"
#include "Text.hpp"
#include "PerformanceStatisticManager.hpp"
#include "Window.hpp"
#include "Renderer.hpp"

#include "glm/glm.hpp"

#include <vector>
#include <memory>

namespace Charly {

    class OpenGLapp {
    private:
        Window mWindow;
        InputHandler mInputHandel;
        Renderer mRenderer;
        Camera mCamera;

        PointLight mPointLight;
        AmbientLight mAmbientLight;

        std::shared_ptr<Model> mModel;
        std::shared_ptr<Text> mText;
        std::shared_ptr<PerformanceStatisticManager> mPerformanceStatisticManager;

        void createModels();

        void handleEvents();
        void update(float dt);
        void render();

    public:
        OpenGLapp();
        ~OpenGLapp();

        void run();

    };

}

#endif //CHAMLY_3D_ENGINE_OPENGLAPP_HPP
