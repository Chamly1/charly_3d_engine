#ifndef CHARLY_3D_ENGINE_FONT_HPP
#define CHARLY_3D_ENGINE_FONT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"

namespace Charly {

    class Font {
    private:
        Texture mGlyphAtlasTexture;
        std::unique_ptr<VertexArray> mVAO;

    public:
        Font(const char* fontPath);
        void draw();

    };

}

#endif //CHARLY_3D_ENGINE_FONT_HPP
