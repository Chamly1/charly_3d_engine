#ifndef CHARLY_3D_ENGINE_TEXT_HPP
#define CHARLY_3D_ENGINE_TEXT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Font.hpp"
#include "Model.hpp"

#include <memory>

namespace Charly {

    // Origin of the text located in the top left corner
    class Text : public Model {
    private:
        std::shared_ptr<Font> mFont;
        unsigned int mFontSize;

    public:
        Text(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& shader, const char* str, unsigned int fontSize);

        void setString(const char* str);

    };

}

#endif //CHARLY_3D_ENGINE_TEXT_HPP
