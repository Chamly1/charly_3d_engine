#include "Font.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include "gl/glew.h"

#include <iostream>

static const unsigned int DEFAULT_FONT_SIZE = 1000;

namespace Charly {

    Font::Font(const char* fontPath) {
        FT_Library ftLib;
        if (FT_Init_FreeType(&ftLib)) {
            std::cout << "ERROR::FreeType: could not init FreeType library\n";
//            return 1;
        }

        FT_Face face;
        if (FT_New_Face(ftLib, fontPath, 0, &face)) {
            std::cout << "ERROR::FreeType: failed to load font\n";
//            return 1;
        }

        FT_Set_Pixel_Sizes(face, 0, DEFAULT_FONT_SIZE);

        ///////////////////////////////////

        if (FT_Load_Char(face, 'F', FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FreeType: failed to load glyph\n";
//            return 1;
        }

        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



        ////////////////////////////

        float vertices[] = {
//                0.0f, 0.0f, 0.0f, 0.0f,
//                0.0f, 1.0f, 0.0f, 1.0f,
//                1.0f, 1.0f, 1.0f, 1.0f,
//
//                0.0f, 0.0f, 0.0f, 0.0f,
//                1.0f, 1.0f, 1.0f, 1.0f,
//                1.0f, 0.0f, 1.0f, 0.0f

                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 500.0f, 0.0f, 1.0f,
                500.0f, 500.0f, 1.0f, 1.0f,

                0.0f, 0.0f, 0.0f, 0.0f,
                500.0f, 500.0f, 1.0f, 1.0f,
                500.0f, 0.0f, 1.0f, 0.0f
        };

        BufferLayout bufferLayout = {
                {ShaderDataType::Float2, "vertexPos"},
                {ShaderDataType::Float2, "texturePos"}
        };
        std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        mVAO = std::make_unique<VertexArray>(vertexBuffer, bufferLayout, sizeof(vertices) / bufferLayout.getStride());

        FT_Done_Face(face);
        FT_Done_FreeType(ftLib);
    }

    void Font::draw() {
        glBindTexture(GL_TEXTURE_2D, mTexture);
        mVAO->draw();
    }

}
