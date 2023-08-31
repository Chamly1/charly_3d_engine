#include "VertexBuffer.hpp"

namespace Charly {

    VertexBuffer::VertexBuffer(float* vertices, unsigned int size, const BufferLayout& layout)
    : mLayout(layout) {
        glCreateBuffers(1, &mVBO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteBuffers(1, &mVBO);
    }

    void VertexBuffer::bind() const {
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    }

    void VertexBuffer::unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    const BufferLayout& VertexBuffer::getLayout() const {
        return mLayout;
    }

//    void VertexBuffer::setLayout(const BufferLayout& layout) {
//        mLayout = layout;
//    }

}
