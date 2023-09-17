#ifndef CHARLY_3D_ENGINE_TEXT_HPP
#define CHARLY_3D_ENGINE_TEXT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Font.hpp"

#include <memory>

namespace Charly {

    class Text {
    private:
        std::shared_ptr<Texture> mGlyphAtlasTexture;
        std::unique_ptr<VertexArray> mVAO;

    public:
        Text(Font& font, const char* str, unsigned int fontSize);

        void draw();

    };

}

#endif //CHARLY_3D_ENGINE_TEXT_HPP
