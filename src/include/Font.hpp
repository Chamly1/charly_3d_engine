#ifndef CHARLY_3D_ENGINE_FONT_HPP
#define CHARLY_3D_ENGINE_FONT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"
#include "GlyphAtlas.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

#include <map>
#include <memory>

namespace Charly {

    class Font {
    private:
        FT_Face mFtFace;
        std::map<unsigned int, std::shared_ptr<GlyphAtlas>> mGlyphAtlases;

    public:
        Font(const char* fontPath);
        ~Font();

        std::unique_ptr<VertexArray> createTextVAO(const char* str, unsigned int fontSize);
        std::shared_ptr<Texture> getGlyphAtlasTexture(unsigned int fontSize) const;

    };

}

#endif //CHARLY_3D_ENGINE_FONT_HPP
