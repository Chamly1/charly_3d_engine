#ifndef CHAMLY_3D_ENGINE_TEXTURE_HPP
#define CHAMLY_3D_ENGINE_TEXTURE_HPP

#include "GL/glew.h"
#include "stb/stb_image.h"

namespace Charly {

    enum class TextureDataFormat {
        RGB,
        RGBA
    };

    class Texture {
    private:
        GLuint mTextureID;
        int mWidth, mHeight, mBitDepth;

    public:
        Texture();
        Texture(const unsigned char* data, unsigned int width, unsigned int height, TextureDataFormat dataFormat);
        Texture(const char* filePath, TextureDataFormat dataFormat);
        ~Texture();

        void init(const unsigned char* data, unsigned int width, unsigned int height, TextureDataFormat dataFormat);
        void useTexture();

        // delete implicit methods
        Texture(Texture const &) = delete;
        Texture & operator = (Texture const &) = delete;
        Texture(Texture &&) = delete;
        Texture & operator = (Texture &&) = delete;

    private:
        void cleanup();

    };

}

#endif //CHAMLY_3D_ENGINE_TEXTURE_HPP
