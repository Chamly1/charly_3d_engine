#include "Text.hpp"
#include "Renderer.hpp"

namespace Charly {

    Text::Text(const std::shared_ptr<Font>& font, const std::shared_ptr<Shader>& shader, const char* str, unsigned int fontSize)
    : mFont(font)
    , mFontSize(fontSize) {
        // need because the order of evaluation of function arguments is unspecified
        mVertexArray = mFont->createTextVAO(str, mFontSize);
        mShader = shader;
        mMaterial = std::make_shared<Material>(mFont->getGlyphAtlasTexture(mFontSize));
    }

    void Text::draw(Renderer& renderer) const {
        mMaterial->bind();

        mShader->bind();
        mShader->uploadUniformMatrix4f("u_Model", calculateModelMatrix());
        mShader->uploadUniformMatrix4f("u_Projection", renderer.getProjectionMatrix());
        mShader->uploadUniformMatrix4f("u_View", renderer.getViewMatrix());

        mShader->uploadUniform3f("u_Color", mMaterial->getColor());

        mVertexArray->draw();
    }

    void Text::setString(const char* str) {
        mVertexArray = mFont->createTextVAO(str, mFontSize);
    }

}
