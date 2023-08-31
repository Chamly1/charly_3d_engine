#ifndef CHAMLY_3D_ENGINE_INDEXBUFFER_HPP
#define CHAMLY_3D_ENGINE_INDEXBUFFER_HPP

#include "GL/glew.h"

namespace Charly {

    class IndexBuffer {
    private:
        GLuint mIBO;
        unsigned int mCount;

    public:
        IndexBuffer(unsigned int* indices, unsigned int count);
        ~IndexBuffer();

        void bind() const;
        void unbind() const;

        unsigned int getCount() const;
    };

}

#endif //CHAMLY_3D_ENGINE_INDEXBUFFER_HPP
