#ifndef LEARN_OPENGL_SHADER_HPP
#define LEARN_OPENGL_SHADER_HPP

#include "GL/glew.h"

#include <string>

class Shader {
private:
    GLuint mShaderID;
    GLuint mUniformModel;
    GLuint mUniformProjection;

    void addShader(const char* shaderCode, GLenum shaderType);
    void compileShader();
    std::string loadShaderFromFile(const char* filePath);

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    GLuint getUniformModel() const;
    GLuint getUniformProjection() const;
    void useShader();

    // delete implicit methods
    Shader(Shader const &) = delete;
    Shader & operator = (Shader const &) = delete;
    Shader(Shader &&) = delete;
    Shader & operator = (Shader &&) = delete;
};

#endif //LEARN_OPENGL_SHADER_HPP
