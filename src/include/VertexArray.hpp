#ifndef CHARLY_3D_ENGINE_VERTEXARRAY_HPP
#define CHARLY_3D_ENGINE_VERTEXARRAY_HPP

#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

#include "GL/glew.h"

#include <memory>

namespace Charly {

    class VertexArray {
    private:
        GLuint mVAO;
        std::shared_ptr<VertexBuffer> mVertexBuffer;
        std::shared_ptr<IndexBuffer> mIndexBuffer;

        void setVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

    public:
        VertexArray(const std::shared_ptr<VertexBuffer>& vertexBuffer, const std::shared_ptr<IndexBuffer>& indexBuffer);

        void bind() const;
        void unbind() const;

        unsigned int getIndicesCount() const;
    };

}

#endif //CHARLY_3D_ENGINE_VERTEXARRAY_HPP
