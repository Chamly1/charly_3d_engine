#include "Text.hpp"

namespace Charly {

    Text::Text(Font& font, const char* str, unsigned int fontSize) {
        mVAO = font.createTextVAO(str, fontSize);
        mGlyphAtlasTexture = font.getGlyphAtlasTexture(fontSize);
    }

    void Text::draw() {
        mGlyphAtlasTexture->bind();
        mVAO->draw();
    }

}
