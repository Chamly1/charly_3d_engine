#ifndef CHAMLY_3D_ENGINE_OPENGLAPP_HPP
#define CHAMLY_3D_ENGINE_OPENGLAPP_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GLFWinputHandler.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Model.hpp"
#include "Text.hpp"
#include "PerformanceStatisticManager.hpp"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <vector>
#include <memory>

namespace Charly {

    class OpenGLapp {
    private:
        GLFWwindow *mWindow;
        GLFWinputHandler mInputHandel;
        Camera mCamera;

        int mFramebufferWidth, mFramebufferHeight;

        std::shared_ptr<Model> mModel;
        std::shared_ptr<Text> mText;
        std::shared_ptr<PerformanceStatisticManager> mPerformanceStatisticManager;

        glm::mat4 mProjectionMatrixPerspective;
        glm::mat4 mProjectionMatrixOrthographic;

        void createAndSetupWindow();
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
