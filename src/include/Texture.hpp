#ifndef LEARN_OPENGL_TEXTURE_HPP
#define LEARN_OPENGL_TEXTURE_HPP

#include "GL/glew.h"
#include "stb/stb_image.h"

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

#endif //LEARN_OPENGL_TEXTURE_HPP
