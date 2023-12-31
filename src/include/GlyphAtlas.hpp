#ifndef CHARLY_3D_ENGINE_GLYPHATLAS_HPP
#define CHARLY_3D_ENGINE_GLYPHATLAS_HPP

#include "Texture.hpp"
#include "VertexBuffer.hpp"

#include "glm/glm.hpp"
#include "freetype/freetype.h"

#include <memory>
#include <map>

namespace Charly {
    struct CharInfo {
        glm::ivec2   size;       // Size of glyph
        glm::ivec2   bearing;    // Offset from baseline to left/top of glyph
        unsigned int advance;    // Offset to advance to next glyph

        glm::fvec2 uvPos;   // glyph texture position on atlas
        glm::fvec2 uvSize;  // glyph texture size on atlas
    };

    class GlyphAtlas {
    private:
        std::shared_ptr<Texture> mGlyphAtlasTexture;
        unsigned int mFontSize; // in pixels
        unsigned int mLineSpacing; // in pixels
        char mFirstChar;
        char mLastChar;
        unsigned int mCharCount;
        std::map<char, CharInfo> mCharInfos;

    public:
        static const BufferLayout bufferLayout; // buffer layout for generated text

        GlyphAtlas(FT_Face& ftFace, char firstChar, char lastChar, unsigned int fontSize);

        std::shared_ptr<VertexBuffer> createTextVBO(const char* str);
        std::shared_ptr<Texture> getGlyphAtlasTexture() const;
    };

}



#endif //CHARLY_3D_ENGINE_GLYPHATLAS_HPP
