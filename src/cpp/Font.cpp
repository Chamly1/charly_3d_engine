#include "Font.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include "gl/glew.h"

#include <iostream>

static const unsigned int DEFAULT_FONT_SIZE = 24;
static FT_Library gFreeTypeLib;
static int gFreeTypeLibUserCount;

namespace Charly {

    Font::Font(const char* fontPath) {
        if (gFreeTypeLibUserCount == 0) {
            if (FT_Init_FreeType(&gFreeTypeLib)) {
                std::cout << "ERROR::FreeType: could not init FreeType library\n";
//            return 1;
            }
        }
        gFreeTypeLibUserCount++;

        FT_Face face;
        if (FT_New_Face(gFreeTypeLib, fontPath, 0, &face)) {
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

        mGlyphAtlasTexture.init(atlasData, atlasWidth, atlasHeight, TextureDataFormat::RGBA);

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
    }

    Font::~Font() {
        gFreeTypeLibUserCount--;
        if (gFreeTypeLibUserCount == 0) {
            FT_Done_FreeType(gFreeTypeLib);
        }
    }

    void Font::draw() {
        mGlyphAtlasTexture.bind();
        mVAO->draw();
    }

}
