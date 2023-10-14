#include "GlyphAtlas.hpp"
#include "Logger.hpp"

#include <iostream>

static const unsigned int VERTICES_PER_GLYPH = 6;
static const unsigned int POINTS_PER_VERTEX = 4;

namespace Charly {

    const BufferLayout GlyphAtlas::bufferLayout = {
            {ShaderDataType::Float2, "vertexPos"},
            {ShaderDataType::Float2, "texturePos"}
    };

    GlyphAtlas::GlyphAtlas(FT_Face& ftFace, char firstChar, char lastChar, unsigned int fontSize) {
        mFontSize = fontSize;
        mFirstChar = firstChar;
        mLastChar = lastChar;
        mCharCount = static_cast<int>(lastChar) - static_cast<int>(firstChar) + 1;

        int atlasWidth;
        int atlasHeight;
        unsigned char* atlasData;

        if (ftFace != nullptr) {

            atlasWidth = fontSize * mCharCount;
            atlasHeight = fontSize;
            atlasData = new unsigned char[atlasWidth * atlasHeight * 4](); // RGBA format

            FT_Set_Pixel_Sizes(ftFace, 0, fontSize);
            // is number of 1/64 pixels, bitshift by 6 to get value in pixels (2^6 = 64)
            mLineSpacing = ftFace->size->metrics.height >> 6;

            int x = 0;
            int y = 0;
            float u = 0.f;
            float v = 0.f;
            glm::fvec2 fontUVSize(1.f / mCharCount, 1.f); // size of one glyph slot in UV coordinates
            glm::fvec2 UVPixelSize(fontUVSize / static_cast<float>(fontSize)); // size of one pixel in UV coordinates
            for (char c = firstChar; c <= lastChar; c++) {
                if (FT_Load_Char(ftFace, c, FT_LOAD_RENDER)) {
                    LOG_ERROR("FreeType: failed to load glyph \'c\'!", c)
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
                        static_cast<unsigned int>(ftFace->glyph->advance.x),

                        glm::fvec2(u, v + 1.f - ((fontUVSize.y / mFontSize) * glyphBitmap.rows)),
                        glm::fvec2(UVPixelSize.x * glyphBitmap.width, UVPixelSize.y * glyphBitmap.rows)
                };

                x += fontSize;
                u += fontUVSize.x;
            }

        } else {
            LOG_WARNING("Passed empty FT_Face for creating glyph atlas. Create fully fill with color stub atlas!")

            atlasWidth = fontSize;
            atlasHeight = fontSize;
            atlasData = new unsigned char[atlasWidth * atlasHeight * 4]; // RGBA format
            memset(atlasData, 255, atlasWidth * atlasHeight * 4);

            mLineSpacing = fontSize;

            for (char c = firstChar; c <= lastChar; c++) {

                mCharInfos[c] = CharInfo{
                        glm::ivec2(fontSize, fontSize),
                        glm::ivec2(fontSize, fontSize),
                        fontSize << 6,

                        glm::fvec2(0.f, 0.f),
                        glm::fvec2(1.f, 1.f),
                };

            }
        }

        mGlyphAtlasTexture = std::make_shared<Texture>(atlasData, atlasWidth, atlasHeight, TextureDataFormat::RGBA);
        delete[] atlasData;
    }

    std::shared_ptr<VertexBuffer> GlyphAtlas::createTextVBO(const char* str) {

        unsigned int bufferCount = strlen(str) * POINTS_PER_VERTEX * VERTICES_PER_GLYPH;
        float* buffer = new float[bufferCount];

        //TODO set start point
        const float xDefault = 0, yDefault = 100;
        float x = xDefault, y = yDefault;

        float xPos, yPos, w, h;
        CharInfo charInfo;
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] == '\n') {
                //TODO add face->ascender and face->descender?
                y -= mLineSpacing;
                x = xDefault;
                continue;
            }

            charInfo = mCharInfos[str[i]];

            xPos = x + charInfo.bearing.x;
            yPos = y - (charInfo.size.y - charInfo.bearing.y);

            w = charInfo.size.x;
            h = charInfo.size.y;

            float tmpGlyphVertices[POINTS_PER_VERTEX * VERTICES_PER_GLYPH] = {
                xPos,     yPos + h, charInfo.uvPos.x,                     charInfo.uvPos.y + charInfo.uvSize.y,
                xPos,     yPos,     charInfo.uvPos.x,                     charInfo.uvPos.y,
                xPos + w, yPos,     charInfo.uvPos.x + charInfo.uvSize.x, charInfo.uvPos.y,

                xPos,     yPos + h, charInfo.uvPos.x,                     charInfo.uvPos.y + charInfo.uvSize.y,
                xPos + w, yPos,     charInfo.uvPos.x + charInfo.uvSize.x, charInfo.uvPos.y,
                xPos + w, yPos + h, charInfo.uvPos.x + charInfo.uvSize.x, charInfo.uvPos.y + charInfo.uvSize.y
            };

            memcpy(&buffer[i * POINTS_PER_VERTEX * VERTICES_PER_GLYPH], tmpGlyphVertices, sizeof(tmpGlyphVertices));

            // advance is number of 1/64 pixels, bitshift by 6 to get value in pixels (2^6 = 64)
            x += charInfo.advance >> 6;
        }

        std::shared_ptr<VertexBuffer> res = std::make_shared<VertexBuffer>(buffer, bufferCount * sizeof(float));
        delete[] buffer;

        return res;
    }

    std::shared_ptr<Texture> GlyphAtlas::getGlyphAtlasTexture() const {
        return mGlyphAtlasTexture;
    }

}
