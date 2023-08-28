#ifndef LEARN_OPENGL_VERTEXBUFFER_HPP
#define LEARN_OPENGL_VERTEXBUFFER_HPP

#include "GL/glew.h"

class VertexBuffer {
private:
    GLuint mVBO;

public:
    VertexBuffer(float* vertices, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif //LEARN_OPENGL_VERTEXBUFFER_HPP
