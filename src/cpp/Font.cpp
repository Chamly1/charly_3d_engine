#include "Font.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include "gl/glew.h"

#include <iostream>

static const unsigned int DEFAULT_FONT_SIZE = 24;

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

        ///////////////////////////////////

//        char firstChar = ' ';
//        char lastChar = '~';
        char firstChar = 'A';
        char lastChar = 'Z';
        int charCount = static_cast<int>(lastChar) - static_cast<int>(firstChar) + 1;
        unsigned int fontSize = 24;
        int atlasWidth = fontSize * charCount;
        int atlasHeight = fontSize;

        unsigned char* atlasData = new unsigned char[atlasWidth * atlasHeight * 4](); // RGBA format

        int x = 0;
        int y = 0;

        FT_Set_Pixel_Sizes(face, 0, fontSize);
        for (char c = firstChar; c <= lastChar; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                // Handle glyph loading error
                continue;
            }

            FT_Bitmap glyphBitmap = face->glyph->bitmap;
            int glyphWidth = glyphBitmap.width;
            int glyphHeight = glyphBitmap.rows;

//            std::cout << "glyphWidth: " << glyphWidth << ";\tglyphHeight: " << glyphHeight << '\n';

            // Copy glyph bitmap data to the atlas image at position (x, y)
            for (int i = 0; i < glyphHeight; i++) {
                for (int j = 0; j < glyphWidth; j++) {
//                    int atlasIndex = ((y + i) * atlasWidth + (x + j)) * 4;
                    // fontSize - 1 - i added to flip atlas upside-down because OpenGL flips textures, but we want to UV's (0, 0) be at left bottom corner
                    int atlasIndex = ((y + fontSize - 1 - i) * atlasWidth + (x + j)) * 4;
                    int glyphIndex = i * glyphWidth + j;

                    atlasData[atlasIndex + 0] = 255; // Red channel
                    atlasData[atlasIndex + 1] = 255; // Green channel
                    atlasData[atlasIndex + 2] = 255; // Blue channel
                    atlasData[atlasIndex + 3] = glyphBitmap.buffer[glyphIndex]; // Alpha channel
                }
            }

            x += fontSize;
        }

        glGenTextures(1, &mTexture);
        glBindTexture(GL_TEXTURE_2D, mTexture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                atlasWidth,
                atlasHeight,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                atlasData
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);



        float vertices[] = {
//                0.0f, 0.0f, 0.0f, 0.0f,
//                0.0f, 1.0f, 0.0f, 1.0f,
//                1.0f, 1.0f, 1.0f, 1.0f,
//
//                0.0f, 0.0f, 0.0f, 0.0f,
//                1.0f, 1.0f, 1.0f, 1.0f,
//                1.0f, 0.0f, 1.0f, 0.0f

//                0.0f, 0.0f, 0.0f, 0.0f,
//                0.0f, 500.0f, 0.0f, 1.0f,
//                500.0f, 500.0f, 1.0f, 1.0f,
//
//                0.0f, 0.0f, 0.0f, 0.0f,
//                500.0f, 500.0f, 1.0f, 1.0f,
//                500.0f, 0.0f, 1.0f, 0.0f

                0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, (float)atlasHeight, 0.0f, 1.0f,
                (float)atlasWidth, (float)atlasHeight, 1.0f, 1.0f,

                0.0f, 0.0f, 0.0f, 0.0f,
                (float)atlasWidth, (float)atlasHeight, 1.0f, 1.0f,
                (float)atlasWidth, 0.0f, 1.0f, 0.0f
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