#include "Texture.hpp"
#include "Logger.hpp"
#include "OpenGLUtils.hpp"

#include <iostream>

namespace Charly {

    static GLenum textureDataFormatToOpenGLType(TextureDataFormat type) {
        switch (type) {
            case TextureDataFormat::RGB:     return GL_RGB;
            case TextureDataFormat::RGBA:    return GL_RGBA;
        }

        return 0;
    }

    Texture::Texture()
    : mTextureID(0)
    , mWidth(0)
    , mHeight(0)
    , mBitDepth(0) {

    }

    Texture::Texture(const unsigned char* data, unsigned int width, unsigned int height, TextureDataFormat dataFormat) {
        init(data, width, height, dataFormat);
    }

    Texture::Texture(const char* filePath, TextureDataFormat dataFormat) {
        int width, height;
        unsigned char* textureData = stbi_load(filePath, &width, &height, &mBitDepth, 0);

        if (!textureData) {
            LOG_ERROR("Texture file \"%s\" read error!", filePath)
            return;
        }

        init(textureData, width, height, dataFormat);

        stbi_image_free(textureData);
    }

    Texture::~Texture() {
        cleanup();
    }

    void Texture::init(const unsigned char* data, unsigned int width, unsigned int height, TextureDataFormat dataFormat) {
        cleanup();

        mWidth = width;
        mHeight = height;

        GL_CALL(glGenTextures(1, &mTextureID))
        GL_CALL(glBindTexture(GL_TEXTURE_2D, mTextureID))

        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT))
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT))
//    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR))
        GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR))

        GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, textureDataFormatToOpenGLType(dataFormat), mWidth, mHeight, 0, textureDataFormatToOpenGLType(dataFormat), GL_UNSIGNED_BYTE, data))
        GL_CALL(glGenerateMipmap(GL_TEXTURE_2D))

        GL_CALL(glBindTexture(GL_TEXTURE_2D, 0))
    }

    void Texture::bind() {
        GL_CALL(glActiveTexture(GL_TEXTURE0))
        GL_CALL(glBindTexture(GL_TEXTURE_2D, mTextureID))
    }

    void Texture::cleanup() {
        if (mTextureID != 0) {
            GL_CALL(glDeleteTextures(1, &mTextureID))
            mTextureID = 0;
            mHeight = 0;
            mWidth = 0;
            mBitDepth = 0;
        }
    }

}
