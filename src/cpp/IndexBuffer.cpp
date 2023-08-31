#include "IndexBuffer.hpp"

namespace Charly {

    IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
            : mCount(count) {
        glCreateBuffers(1, &mIBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer() {
        glDeleteBuffers(1, &mIBO);
    }

    void IndexBuffer::bind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    }

    void IndexBuffer::unbind() const {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

}
