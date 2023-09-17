#include "VertexArray.hpp"
#include "BufferLayout.hpp"

namespace Charly {

    void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) {
        glBindVertexArray(mVAO);
        vertexBuffer->bind();
        unsigned int index = 0;
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

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, const BufferLayout& layout)
    : mCount(indexBuffer->getCount()) {
        glCreateVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);
        setVertexBuffer(vertexBuffer, layout);
        setIndexBuffer(indexBuffer);
        glBindVertexArray(0);
    }

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
    : mIndexBuffer(nullptr)
    , mCount(vertexBuffer->getSize() / layout.getStride()) {
        glCreateVertexArrays(1, &mVAO);
        glBindVertexArray(mVAO);
        setVertexBuffer(vertexBuffer, layout);
        glBindVertexArray(0);
    }

    void VertexArray::bind() const {
        glBindVertexArray(mVAO);
    }

    void VertexArray::unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::draw() const {
        glBindVertexArray(mVAO);
        if (mIndexBuffer) {
            glDrawElements(GL_TRIANGLES, mCount, GL_UNSIGNED_INT, 0);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, mCount);
        }
        glBindVertexArray(0);
    }

    unsigned int VertexArray::getIndicesCount() const {
        return mIndexBuffer->getCount();
    }

}
