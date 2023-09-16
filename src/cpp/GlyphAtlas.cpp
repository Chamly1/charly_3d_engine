#include "GlyphAtlas.hpp"

#include <iostream>

namespace Charly {

    GlyphAtlas::GlyphAtlas(FT_Face& ftFace, char firstChar, char lastChar, unsigned int fontSize) {
        mFontSize = fontSize;
        mFirstChar = firstChar;
        mLastChar = lastChar;
        mCharCount = static_cast<int>(lastChar) - static_cast<int>(firstChar) + 1;

        int atlasWidth = fontSize * mCharCount;
        int atlasHeight = fontSize;

        unsigned char* atlasData = new unsigned char[atlasWidth * atlasHeight * 4](); // RGBA format

        FT_Set_Pixel_Sizes(ftFace, 0, fontSize);

        int x = 0;
        int y = 0;
        for (char c = firstChar; c <= lastChar; c++) {
            if (FT_Load_Char(ftFace, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FreeType: failed to load glyph\n";
//                return 1;
            }

            FT_Bitmap glyphBitmap = ftFace->glyph->bitmap;

            // Copy glyph bitmap data to the atlas image at position (x, y)
            for (int i = 0; i < glyphBitmap.rows; i++) {
                for (int j = 0; j < glyphBitmap.width; j++) {
//                    int atlasIndex = ((y + i) * atlasWidth + (x + j)) * 4;
                    // fontSize - 1 - i added to flip atlas upside-down because OpenGL flips textures, but we want to UV's (0, 0) be at left bottom corner
                    int atlasIndex = ((y + fontSize - 1 - i) * atlasWidth + (x + j)) * 4;
                    int glyphIndex = i * glyphBitmap.width + j;

                    atlasData[atlasIndex + 0] = 255; // Red channel
                    atlasData[atlasIndex + 1] = 255; // Green channel
                    atlasData[atlasIndex + 2] = 255; // Blue channel
                    atlasData[atlasIndex + 3] = glyphBitmap.buffer[glyphIndex]; // Alpha channel
                }
            }

            mCharInfos[c] = CharInfo{
                    glm::ivec2(glyphBitmap.width, glyphBitmap.rows),
                    glm::ivec2(ftFace->glyph->bitmap_left, ftFace->glyph->bitmap_top),
                    static_cast<unsigned int>(ftFace->glyph->advance.x)
            };

            x += fontSize;
        }

        mGlyphAtlasTexture = std::make_shared<Texture>(atlasData, atlasWidth, atlasHeight, TextureDataFormat::RGBA);
        delete[] atlasData;
    }

    std::shared_ptr<Texture> GlyphAtlas::getGlyphAtlasTexture() const {
        return mGlyphAtlasTexture;
    }

}
