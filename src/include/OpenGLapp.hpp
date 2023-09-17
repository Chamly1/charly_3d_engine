#ifndef CHAMLY_3D_ENGINE_OPENGLAPP_HPP
#define CHAMLY_3D_ENGINE_OPENGLAPP_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GLFWinputHandler.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

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

        std::vector<std::unique_ptr<VertexArray>> mVertexArrays;
        std::vector<std::unique_ptr<Shader>> mShaderArray;
        std::vector<std::unique_ptr<Texture>> mTextureArray;

        glm::mat4 mProjectionMatrixPerspective;
        glm::mat4 mProjectionMatrixOrthographic;

        void createAndSetupWindow();
        void createVertexArrays();
        void createShaders();
        void createTextures();

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
