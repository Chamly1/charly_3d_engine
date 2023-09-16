#ifndef CHARLY_3D_ENGINE_GLYPHATLAS_HPP
#define CHARLY_3D_ENGINE_GLYPHATLAS_HPP

#include "Texture.hpp"

#include "glm/glm.hpp"
#include "freetype/freetype.h"

#include <memory>
#include <map>

namespace Charly {
    struct CharInfo {
        glm::ivec2   size;       // Size of glyph
        glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
        unsigned int advance;    // Offset to advance to next glyph
    };

    class GlyphAtlas {
    private:
        std::shared_ptr<Texture> mGlyphAtlasTexture;
        unsigned int mFontSize;
        char mFirstChar;
        char mLastChar;
        unsigned int mCharCount;
        std::map<char, CharInfo> mCharInfos;

    public:
        GlyphAtlas(FT_Face& mFtFace, char firstChar, char lastChar, unsigned int fontSize);

    };

}



#endif //CHARLY_3D_ENGINE_GLYPHATLAS_HPP
