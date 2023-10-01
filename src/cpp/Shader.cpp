#include "Shader.hpp"
#include "Logger.hpp"

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
        GLuint shader = glCreateShader(shaderType);

        const GLchar* code[1];
        code[0] = shaderCode;

        GLint codeLength[1];
        codeLength[0] = strlen(shaderCode);

        glShaderSource(shader, 1, code, codeLength);
        glCompileShader(shader);

        GLint res = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
        if (!res) {
            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            char *log = new char[logLength];
            glGetShaderInfoLog(shader, logLength, NULL, log);
            LOG_ERROR("Shader compiling error!\n%s\n", log)
            delete[] log;
//        glDeleteShader(shader);
            return;
        }

        glAttachShader(mShaderID, shader);
    }

    void Shader::linkAndValidateProgram() {
        GLint res = 0;

        glLinkProgram(mShaderID);
        glGetProgramiv(mShaderID, GL_LINK_STATUS, &res);
        if (!res) {
            GLint logLength;
            glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &logLength);
            char *log = new char[logLength];
            glGetProgramInfoLog(mShaderID, logLength, NULL, log);
            LOG_ERROR("Linking program error!\n%s\n", log)
            delete[] log;
            return;
        }

        glValidateProgram(mShaderID);
        glGetProgramiv(mShaderID, GL_VALIDATE_STATUS, &res);
        if (!res) {
            GLint logLength;
            glGetProgramiv(mShaderID, GL_INFO_LOG_LENGTH, &logLength);
            char *log = new char[logLength];
            glGetProgramInfoLog(mShaderID, logLength, NULL, log);
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

        mShaderID = glCreateProgram();
        if (!mShaderID) {
            LOG_ERROR("Create shader program error!")
            return;
        }

        compileAndAttachShader(vertexShaderCode, GL_VERTEX_SHADER);
        compileAndAttachShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
        linkAndValidateProgram();
    }

    Shader::~Shader() {
        glDeleteProgram(mShaderID);
    }

    void Shader::bind() const {
        glUseProgram(mShaderID);
    }

    void Shader::unbind() const {
        glUseProgram(0);
    }

    void Shader::uploadUniform1f(const std::string& name, float value) {
        GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str());
        glUniform1f(uniformLocation, value);
    }

    void Shader::uploadUniform3f(const std::string& name, const glm::vec3& value) {
        GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str());
        glUniform3fv(uniformLocation, 1, glm::value_ptr(value));
    }

    void Shader::uploadUniform4f(const std::string& name, const glm::vec4& value) {
        GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str());
        glUniform4fv(uniformLocation, 1, glm::value_ptr(value));
    }

    void Shader::uploadUniformMatrix4f(const std::string& name, const glm::mat4& value) {
        GLint uniformLocation = glGetUniformLocation(mShaderID, name.c_str());
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
    }

}
