#include "Shader.hpp"

#include "glm/gtc/type_ptr.hpp"

#include <iostream>
#include <fstream>

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
        std::cout << "Shader compiling error!\n" << log << "\n";
        delete[] log;
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
        std::cout << "Linking program error!\n" << log << "\n";
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
        std::cout << "Error validation program: " << log << "\n";
        delete[] log;
        return;
    }
}

std::string Shader::loadShaderFromFile(const char* filePath) {
    std::string shaderStr = "";
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream) {
        std::cout << "Shader file read error! File: " << filePath << '\n';
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

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
    std::string vertexShaderCodeString = loadShaderFromFile(vertexShaderPath);
    const char* vertexShaderCode = vertexShaderCodeString.c_str();
    std::string fragmentShaderCodeString = loadShaderFromFile(fragmentShaderPath);
    const char* fragmentShaderCode = fragmentShaderCodeString.c_str();

    mShaderID = glCreateProgram();
    if (!mShaderID) {
        std::cout << "Create shader program error!\n";
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

void Shader::uploadUniformMatrix4f(const std::string& name, const glm::mat4& value) {
    GLuint uniformLocation = glGetUniformLocation(mShaderID, name.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}
