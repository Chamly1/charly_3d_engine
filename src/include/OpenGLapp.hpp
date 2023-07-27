#ifndef LEARN_OPENGL_OPENGLAPP_HPP
#define LEARN_OPENGL_OPENGLAPP_HPP

#include "Mesh.hpp"
#include "Shader.hpp"
#include "GLFWinputHandler.hpp"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <vector>
#include <memory>

class OpenGLapp {
private:
    GLFWwindow *mWindow;
    GLFWinputHandler mInputHandel;

    int mFramebufferWidth, mFramebufferHeight;

    std::vector<std::unique_ptr<Mesh>> mMeshArray;
    std::vector<std::unique_ptr<Shader>> mShaderArray;

    glm::mat4 mProjectionMatrix;

    void createAndSetupWindow();
    void createMeshes();
    void createShaders();

    void handleEvents();
    void update();
    void render();

public:
    OpenGLapp();
    ~OpenGLapp();

    void run();

};

#endif //LEARN_OPENGL_OPENGLAPP_HPP
