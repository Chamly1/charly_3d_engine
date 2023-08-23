#include "Texture.hpp"

#include <iostream>

Texture::Texture(const char* filePath, bool includeAlphaChanel) {
    unsigned char* textureData = stbi_load(filePath, &mWidth, &mHeight, &mBitDepth, 0);

    if (!textureData) {
        std::cout << "Texture file read error! File: " << filePath << '\n';
        return;
    }

    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLint internalformat;
    if (includeAlphaChanel) {
        internalformat = GL_RGBA;
    } else {
        internalformat = GL_RGB;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, internalformat, mWidth, mHeight, 0, internalformat, GL_UNSIGNED_BYTE, textureData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(textureData);
}

Texture::~Texture() {
    glDeleteTextures(1, &mTextureID);
}

void Texture::useTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}