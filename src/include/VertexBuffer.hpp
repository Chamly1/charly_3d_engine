#ifndef LEARN_OPENGL_VERTEXBUFFER_HPP
#define LEARN_OPENGL_VERTEXBUFFER_HPP

#include "BufferLayout.hpp"

#include "GL/glew.h"

class VertexBuffer {
private:
    GLuint mVBO;
    BufferLayout mLayout;

public:
    VertexBuffer(float* vertices, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;

    const BufferLayout& getLayout() const;
    void setLayout(const BufferLayout& layout);
};

#endif //LEARN_OPENGL_VERTEXBUFFER_HPP
