#include "VertexArray.hpp"
#include "BufferLayout.hpp"
#include "OpenGLUtils.hpp"

namespace Charly {

    void VertexArray::setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout) {
        GL_CALL(glBindVertexArray(mVAO))
        vertexBuffer->bind();
        unsigned int index = 0;
        for (const auto& element : layout.getElements()) {
            GL_CALL(glEnableVertexAttribArray(index))
            GL_CALL(glVertexAttribPointer(index,
                                  getShaderDataTypeElementCount(element.type),
                                  shaderDataTypeToOpenGLBaseType(element.type),
                                  element.normalized ? GL_TRUE : GL_FALSE,
                                  layout.getStride(),
                                  reinterpret_cast<void*>(element.offset)))
            index++;
        }

        mVertexBuffer = vertexBuffer;
    }

    void VertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
        GL_CALL(glBindVertexArray(mVAO))
        indexBuffer->bind();

        mIndexBuffer = indexBuffer;
    }

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer, const BufferLayout& layout)
    : mCount(indexBuffer->getCount()) {
        GL_CALL(glCreateVertexArrays(1, &mVAO))
        GL_CALL(glBindVertexArray(mVAO))
        setVertexBuffer(vertexBuffer, layout);
        setIndexBuffer(indexBuffer);
        GL_CALL(glBindVertexArray(0))
    }

    VertexArray::VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const BufferLayout& layout)
    : mIndexBuffer(nullptr)
    , mCount(vertexBuffer->getSize() / layout.getStride()) {
        GL_CALL(glCreateVertexArrays(1, &mVAO))
        GL_CALL(glBindVertexArray(mVAO))
        setVertexBuffer(vertexBuffer, layout);
        GL_CALL(glBindVertexArray(0))
    }

    void VertexArray::bind() const {
        GL_CALL(glBindVertexArray(mVAO))
    }

    void VertexArray::unbind() const {
        GL_CALL(glBindVertexArray(0))
    }

    void VertexArray::draw() const {
        GL_CALL(glBindVertexArray(mVAO))
        if (mIndexBuffer) {
            GL_CALL(glDrawElements(GL_TRIANGLES, mCount, GL_UNSIGNED_INT, 0))
        } else {
            GL_CALL(glDrawArrays(GL_TRIANGLES, 0, mCount))
        }
        GL_CALL(glBindVertexArray(0))
    }

    unsigned int VertexArray::getIndicesCount() const {
        return mIndexBuffer->getCount();
    }

}
