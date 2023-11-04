#ifndef CHARLY_3D_ENGINE_TEXT_HPP
#define CHARLY_3D_ENGINE_TEXT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Font.hpp"
#include "Model.hpp"

#include <memory>

namespace Charly {

    class Text : public Model {
    private:
        std::shared_ptr<Font> mFont;

    public:
        Text(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& shader, const char* str, unsigned int fontSize);

    };

}

#endif //CHARLY_3D_ENGINE_TEXT_HPP
