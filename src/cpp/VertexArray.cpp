#include "VertexArray.hpp"
#include "BufferLayout.hpp"

namespace Charly {

    void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
        glBindVertexArray(mVAO);
        vertexBuffer->bind();
        unsigned int index = 0;
        const auto& layout = vertexBuffer->getLayout();
        for (const auto& element : layout.getElements()) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                                  getShaderDataTypeElementCount(element.type),
                                  shaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  reinterpret_cast<void*>(element.offset));
            index++;
        }

        mVertexBuffer = vertexBuffer;
    }

    void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        glBindVertexArray(mVAO);
        indexBuffer->bind();

        mIndexBuffer = indexBuffer;
    }

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer) {
        glCreateVertexArrays(1, &mVAO);
        setVertexBuffer(vertexBuffer);
        setIndexBuffer(indexBuffer);
    }

    void VertexArray::bind() const {
        glBindVertexArray(mVAO);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    unsigned int VertexArray::getIndicesCount() const {
        return mIndexBuffer->getCount();
    }

}
