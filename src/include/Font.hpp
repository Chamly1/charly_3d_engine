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

    /**
     * Class to load a font from a file and use it to generate a text mesh.
     */
    class Font {
    private:
        FT_Face mFtFace;
        std::map<unsigned int, std::shared_ptr<GlyphAtlas>> mGlyphAtlases; // map<font size, glyph atlas>

    public:
        /**
         * Construct a Font object with a font file.
         * If there will be an error during the file loading, the object steel will be created but with the internal
         * stub state which will allow to use this object, but glyphs will be replaced with simple fill color.
         *
         * @param fontPath path to a font file.
         */
        Font(const char* fontPath);
        ~Font();

        std::shared_ptr<VertexArray> createTextVAO(const char* str, unsigned int fontSize);
        std::shared_ptr<Texture> getGlyphAtlasTexture(unsigned int fontSize) const;

    };

}

#endif //CHARLY_3D_ENGINE_FONT_HPP
