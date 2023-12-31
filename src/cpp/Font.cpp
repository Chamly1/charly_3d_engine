#include "Font.hpp"
#include "Logger.hpp"

#include <iostream>

static const char DEFAULT_ATLAS_FIRST_CHAR = ' ';
static const char DEFAULT_ATLAS_LAST_CHAR = '~';
static const unsigned int DEFAULT_FONT_SIZE = 24;

static FT_Library gFreeTypeLib;
static int gFreeTypeLibUserCount;

namespace Charly {

    Font::Font(const char* fontPath)
    : mFtFace(nullptr) {
        if (gFreeTypeLibUserCount == 0) {
            if (FT_Init_FreeType(&gFreeTypeLib)) {
                LOG_ERROR("FreeType: could not init FreeType library!")
            }
        }
        gFreeTypeLibUserCount++;

        if (FT_New_Face(gFreeTypeLib, fontPath, 0, &mFtFace)) {
            LOG_ERROR("FreeType: failed to load font file \"%s\"!", fontPath)
        }

    }

    Font::~Font() {
        if (mFtFace != nullptr && FT_Done_Face(mFtFace) != 0) {
            LOG_ERROR("FreeType: error during discarding a face object!")
        }
        gFreeTypeLibUserCount--;
        if (gFreeTypeLibUserCount == 0) {
            if (FT_Done_FreeType(gFreeTypeLib) != 0) {
                LOG_ERROR("FreeType: error during destroying a FreeType library object!")
            }
        }
    }

    std::shared_ptr<VertexArray> Font::createTextVAO(const char* str, unsigned int fontSize) {
        std::shared_ptr<GlyphAtlas> glyphAtlas;
        if (mGlyphAtlases.count(fontSize)) {
            glyphAtlas = mGlyphAtlases[fontSize];
        } else {
            glyphAtlas = std::make_shared<GlyphAtlas>(mFtFace, DEFAULT_ATLAS_FIRST_CHAR, DEFAULT_ATLAS_LAST_CHAR, fontSize);
            mGlyphAtlases[fontSize] = glyphAtlas;
        }

        std::shared_ptr<VertexBuffer> VBO = glyphAtlas->createTextVBO(str);

        return std::make_shared<VertexArray>(VBO, glyphAtlas->bufferLayout);
    }

    std::shared_ptr<Texture> Font::getGlyphAtlasTexture(unsigned int fontSize) const {
        try {
            return mGlyphAtlases.at(fontSize)->getGlyphAtlasTexture();
        } catch (const std::out_of_range&) {
            LOG_ERROR("There is no glyph atlases for specified font size!")
            return nullptr;
        }
    }

}
