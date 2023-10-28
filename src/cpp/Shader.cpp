#include "Shader.hpp"
#include "Logger.hpp"
#include "OpenGLUtils.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>

namespace Charly {

    std::string Shader::loadShaderFromFile(const char* filePath) {
        std::string shaderStr = "";
        std::ifstream fileStream(filePath, std::ios::in);

        if (!fileStream) {
            LOG_ERROR("Shader file \"%s\" read error!", filePath)
            return "";
        }

        std::string line = "";
        while (!fileStream.eof()) {
            std::getline(fileStream, line);
            shaderStr.append(line + "\n");
        }

        fileStream.close();

        return shaderStr;
    }

    void Shader::compileAndAttachShader(const char* shaderCode, GLenum shaderType) {
        GL_CALL(GLuint shader = glCreateShader(shaderType))

        const GLchar* code[1];
        code[0] = shaderCode;

        GLint codeLength[1];
        codeLength[0] = strlen(shaderCode);

        GL_CALL(glShaderSource(shader, 1, code, codeLength))
        GL_CALL(glCompileShader(shader))

        GLint res = 0;
        GL_CALL(glGetShaderiv(shader, GL_COMPILE_STATUS, &res))
        if (!res) {
            GLint logLength;
            GL_CALL(glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength))
            char *log = new char[logLength];
            GL_CALL(glGetShaderInfoLog(shader, logLength, NULL, log))
            LOG_ERROR("Shader compiling error!\n%s\n", log)
            delete[] log;
//        glDeleteShader(shader);
            return;
        }

        GL_CALL(glAttachShader(mShaderID, shader))
    }

    void Shader::linkAndValidateProgram() {
        GLint res = 0;

        GL_CALL(glLinkProgram(mShaderID))
        GL_CALL(glGetProgramiv(mShaderID, GL_LINK_STATUS, &res))
        if (!res) {
            GLint logLength;
            GL_CALL(glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &logLength))
            char *log = new char[logLength];
            GL_CALL(glGetProgramInfoLog(mShaderID, logLength, NULL, log))
            LOG_ERROR("Linking program error!\n%s\n", log)
            delete[] log;
            return;
        }

        GL_CALL(glValidateProgram(mShaderID))
        GL_CALL(glGetProgramiv(mShaderID, GL_VALIDATE_STATUS, &res))
        if (!res) {
            GLint logLength;
            GL_CALL(glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &logLength))
            char *log = new char[logLength];
            GL_CALL(glGetProgramInfoLog(mShaderID, logLength, NULL, log))
            LOG_ERROR("Error validation program!\n%s\n", log)
            delete[] log;
            return;
        }
    }

    Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
        std::string vertexShaderCodeString = loadShaderFromFile(vertexShaderPath);
        const char* vertexShaderCode = vertexShaderCodeString.c_str();
        std::string fragmentShaderCodeString = loadShaderFromFile(fragmentShaderPath);
        const char* fragmentShaderCode = fragmentShaderCodeString.c_str();

        GL_CALL(mShaderID = glCreateProgram())
        if (!mShaderID) {
            LOG_ERROR("Create shader program error!")
            return;
        }

        compileAndAttachShader(vertexShaderCode, GL_VERTEX_SHADER);
        compileAndAttachShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
        linkAndValidateProgram();
    }

    Shader::~Shader() {
        GL_CALL(glDeleteProgram(mShaderID))
    }

    void Shader::bind() const {
        GL_CALL(glUseProgram(mShaderID))
    }

    void Shader::unbind() const {
        GL_CALL(glUseProgram(0))
    }

    void Shader::uploadUniform1f(const std::string& name, float value) {
        GL_CALL(GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str()))
        GL_CALL(glUniform1f(uniformLocation, value))
    }

    void Shader::uploadUniform3f(const std::string& name, const glm::vec3& value) {
        GL_CALL(GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str()))
        GL_CALL(glUniform3fv(uniformLocation, 1, glm::value_ptr(value)))
    }

    void Shader::uploadUniform4f(const std::string& name, const glm::vec4& value) {
        GL_CALL(GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str()))
        GL_CALL(glUniform4fv(uniformLocation, 1, glm::value_ptr(value)))
    }

    void Shader::uploadUniformMatrix4f(const std::string& name, const glm::mat4& value) {
        GL_CALL(GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str()))
        GL_CALL(glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value)))
    }

}
