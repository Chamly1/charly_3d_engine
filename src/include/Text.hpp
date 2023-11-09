#ifndef CHARLY_3D_ENGINE_TEXT_HPP
#define CHARLY_3D_ENGINE_TEXT_HPP

#include "Texture.hpp"
#include "VertexArray.hpp"
#include "Font.hpp"
#include "Model.hpp"

#include <memory>

namespace Charly {

    // Origin of the text located in the top left corner
    class Text : public Transformable, public Drawable {
    private:
        std::shared_ptr<VertexArray> mVertexArray;
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<Material> mMaterial;
        std::shared_ptr<Font> mFont;
        unsigned int mFontSize;

    protected:
        void draw(Renderer& renderer) const override;

    public:
        Text(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& shader, const char* str, unsigned int fontSize);

        void setString(const char* str);

        // delete implicit methods
        Text(Text const &) = delete;
        Text & operator = (Text const &) = delete;
        Text(Text &&) = delete;
        Text & operator = (Text &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_TEXT_HPP
