#include "IndexBuffer.hpp"
#include "OpenGLUtils.hpp"

namespace Charly {

    IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
            : mCount(count) {
        GL_CALL(glCreateBuffers(1, &mIBO))
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO))
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW))
    }

    IndexBuffer::~IndexBuffer() {
        GL_CALL(glDeleteBuffers(1, &mIBO))
    }

    void IndexBuffer::bind() const {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO))
    }

    void IndexBuffer::unbind() const {
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
    }

    unsigned int IndexBuffer::getCount() const {
        return mCount;
    }

}
