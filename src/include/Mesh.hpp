#ifndef CHAMLY_3D_ENGINE_MESH_HPP
#define CHAMLY_3D_ENGINE_MESH_HPP

#include "GL/glew.h"

namespace Charly {

    class Mesh {
    private:
        GLuint mVAO, mVBO, mIBO;
        GLsizei mIndexCount;

    public:
        Mesh(GLfloat *vertices, unsigned int verticesNum, unsigned int *indices, unsigned int indicesNum, bool includeUVCoordinate);
        ~Mesh();

        void render();

        // delete implicit methods
        Mesh(Mesh const &) = delete;
        Mesh & operator = (Mesh const &) = delete;
        Mesh(Mesh &&) = delete;
        Mesh & operator = (Mesh &&) = delete;
    };

}

#endif //CHAMLY_3D_ENGINE_MESH_HPP
