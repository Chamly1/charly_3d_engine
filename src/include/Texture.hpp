#ifndef CHAMLY_3D_ENGINE_TEXTURE_HPP
#define CHAMLY_3D_ENGINE_TEXTURE_HPP

#include "GL/glew.h"
#include "stb/stb_image.h"

namespace Charly {

    class Texture {
    private:
        GLuint mTextureID;
        int mWidth, mHeight, mBitDepth;

    public:
        Texture(const char* filePath, bool includeAlphaChanel);
        ~Texture();

        void useTexture();

        // delete implicit methods
        Texture(Texture const &) = delete;
        Texture & operator = (Texture const &) = delete;
        Texture(Texture &&) = delete;
        Texture & operator = (Texture &&) = delete;
    };

}

#endif //CHAMLY_3D_ENGINE_TEXTURE_HPP
