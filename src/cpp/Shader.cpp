#include "Shader.hpp"

#include <iostream>
#include <fstream>

void Shader::addShader(const char* shaderCode, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);

    const GLchar* code[1];
    code[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, code, codeLength);
    glCompileShader(shader);

    GLint res = 0;
    GLchar log[1024] = { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
    if (!res) {
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        std::cout << "Error shader compiling: " << log << "\n";
        return;
    }

    glAttachShader(mShaderID, shader);
}

void Shader::compileShader() {
    GLint res = 0;
    GLchar log[1024] = { 0 };

    glLinkProgram(mShaderID);
    glGetProgramiv(mShaderID, GL_LINK_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(mShaderID, sizeof(log), NULL, log);
        std::cout << "Error linking program: " << log << "\n";
        return;
    }

    glValidateProgram(mShaderID);
    glGetProgramiv(mShaderID, GL_VALIDATE_STATUS, &res);
    if (!res) {
        glGetProgramInfoLog(mShaderID, sizeof(log), NULL, log);
        std::cout << "Error validation program: " << log << "\n";
        return;
    }
}

std::string Shader::loadShaderFromFile(const char* filePath) {
    std::string shaderStr = "";
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream) {
        std::cout << "Shader file read error: " << filePath << '\n';
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

    addShader(vertexShaderCode, GL_VERTEX_SHADER);
    addShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    compileShader();

    mUniformModel = glGetUniformLocation(mShaderID, "model");
    mUniformProjection = glGetUniformLocation(mShaderID, "projection");
}

Shader::~Shader() {
    glDeleteProgram(mShaderID);
}

GLuint Shader::getUniformModel() const {
    return mUniformModel;
}

GLuint Shader::getUniformProjection() const {
    return mUniformProjection;
}

void Shader::useShader() {
    glUseProgram(mShaderID);
}
