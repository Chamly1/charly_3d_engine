#ifndef LEARN_OPENGL_OPENGLAPP_HPP
#define LEARN_OPENGL_OPENGLAPP_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GLFWinputHandler.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

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

        std::vector<std::unique_ptr<Mesh>> mMeshArray;
        std::vector<std::unique_ptr<Shader>> mShaderArray;
        std::vector<std::unique_ptr<Texture>> mTextureArray;

        glm::mat4 mProjectionMatrix;

        void createAndSetupWindow();
        void createMeshes();
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

#endif //LEARN_OPENGL_OPENGLAPP_HPP
