#ifndef CHARLY_3D_ENGINE_FONT_HPP
#define CHARLY_3D_ENGINE_FONT_HPP

#include "VertexArray.hpp"

namespace Charly {

    class Font {
    private:
        unsigned int mTexture;
        std::unique_ptr<VertexArray> mVAO;

    public:
        Font(const char* fontPath);
        void draw();

    };

}

#endif //CHARLY_3D_ENGINE_FONT_HPP
