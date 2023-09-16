#include "Texture.hpp"

#include <iostream>

namespace Charly {

    static GLenum textureDataFormatToOpenGLType(TextureDataFormat type) {
        switch (type) {
            case TextureDataFormat::RGB:     return GL_RGB;
            case TextureDataFormat::RGBA:    return GL_RGBA;
        }

        return 0;
    }

    void Texture::createTexture(const unsigned char* data, unsigned int width, unsigned int height, TextureDataFormat dataFormat) {
        mWidth = width;
        mHeight = height;

        glGenTextures(1, &mTextureID);
        glBindTexture(GL_TEXTURE_2D, mTextureID);

        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, textureDataFormatToOpenGLType(dataFormat), mWidth, mHeight, 0, textureDataFormatToOpenGLType(dataFormat), GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture::Texture(const unsigned char* data, unsigned int width, unsigned int height, TextureDataFormat dataFormat) {
        createTexture(data, width, height, dataFormat);
    }

    Texture::Texture(const char* filePath, TextureDataFormat dataFormat) {
        int width, height;
        unsigned char* textureData = stbi_load(filePath, &width, &height, &mBitDepth, 0);

        if (!textureData) {
            std::cout << "Texture file read error! File: " << filePath << '\n';
            return;
        }

        createTexture(textureData, width, height, dataFormat);

        stbi_image_free(textureData);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &mTextureID);
    }

    void Texture::useTexture() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mTextureID);
    }

}
