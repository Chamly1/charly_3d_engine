#include "VertexBuffer.hpp"
#include "OpenGLUtils.hpp"

namespace Charly {

    VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
    : mSize(size) {
        GL_CALL(glCreateBuffers(1, &mVBO))
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mVBO))
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW))
    }

    VertexBuffer::~VertexBuffer() {
        GL_CALL(glDeleteBuffers(1, &mVBO))
    }

    void VertexBuffer::bind() const {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mVBO))
    }

    void VertexBuffer::unbind() const {
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
    }

    unsigned int VertexBuffer::getSize() const {
        return mSize;
    }

}
