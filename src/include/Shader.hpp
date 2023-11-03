#ifndef CHAMLY_3D_ENGINE_SHADER_HPP
#define CHAMLY_3D_ENGINE_SHADER_HPP

#include "GL/glew.h"
#include "glm/matrix.hpp"

#include <string>

namespace Charly {

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

        void uploadUniform1f(const std::string& name, float value) const;
        void uploadUniform3f(const std::string& name, const glm::vec3& value) const;
        void uploadUniform4f(const std::string& name, const glm::vec4& value) const;
        void uploadUniformMatrix4f(const std::string& name, const glm::mat4& value) const;

        // delete implicit methods
        Shader(Shader const &) = delete;
        Shader & operator = (Shader const &) = delete;
        Shader(Shader &&) = delete;
        Shader & operator = (Shader &&) = delete;
    };

}

#endif //CHAMLY_3D_ENGINE_SHADER_HPP
