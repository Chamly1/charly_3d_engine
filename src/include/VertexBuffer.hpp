#ifndef CHAMLY_3D_ENGINE_VERTEXBUFFER_HPP
#define CHAMLY_3D_ENGINE_VERTEXBUFFER_HPP

#include "BufferLayout.hpp"

#include "GL/glew.h"

namespace Charly {

    class VertexBuffer {
    private:
        GLuint mVBO;

    public:
        VertexBuffer(float* vertices, unsigned int size);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;

    };

}

#endif //CHAMLY_3D_ENGINE_VERTEXBUFFER_HPP
