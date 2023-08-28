#ifndef LEARN_OPENGL_INDEXBUFFER_HPP
#define LEARN_OPENGL_INDEXBUFFER_HPP

#include "GL/glew.h"

class IndexBuffer {
private:
    GLuint mIBO;
    unsigned int mCount;

public:
    IndexBuffer(unsigned int* indices, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
};

#endif //LEARN_OPENGL_INDEXBUFFER_HPP
