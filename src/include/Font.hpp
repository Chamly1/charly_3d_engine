#ifndef CHARLY_3D_ENGINE_FONT_HPP
#define CHARLY_3D_ENGINE_FONT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

namespace Charly {

    class Font {
    private:
        FT_Face mFtFace;

        Texture mGlyphAtlasTexture;
        std::unique_ptr<VertexArray> mVAO;

    public:
        Font(const char* fontPath);
        ~Font();

        void draw();

    };

}

#endif //CHARLY_3D_ENGINE_FONT_HPP
