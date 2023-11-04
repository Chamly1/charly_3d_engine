#include "Text.hpp"

namespace Charly {

    Text::Text(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& shader, const char* str, unsigned int fontSize)
    : mFont(font) {
        // need because the order of evaluation of function arguments is unspecified
        std::shared_ptr<VertexArray> vertexArray = mFont->createTextVAO(str, fontSize);
        std::shared_ptr<Material> material = std::make_shared<Material>(mFont->getGlyphAtlasTexture(fontSize));
        material->setColor(glm::vec3(0.f, 1.f, 0.f));
        init(vertexArray, shader, material);
    }

}
