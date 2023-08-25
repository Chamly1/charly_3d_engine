#ifndef LEARN_OPENGL_SHADER_HPP
#define LEARN_OPENGL_SHADER_HPP

#include "GL/glew.h"
#include "glm/matrix.hpp"

#include <string>

class Shader {
private:
    GLuint mShaderID;

    std::string loadShaderFromFile(const char* filePath);
    void compileAndAttachShader(const char* shaderCode, GLenum shaderType);
    void linkAndValidateProgram();

public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    void uploadUniform4f(const std::string& name, const glm::vec4& value);
    void uploadUniformMatrix4f(const std::string& name, const glm::mat4& value);

    // delete implicit methods
    Shader(Shader const &) = delete;
    Shader & operator = (Shader const &) = delete;
    Shader(Shader &&) = delete;
    Shader & operator = (Shader &&) = delete;
};

#endif //LEARN_OPENGL_SHADER_HPP
