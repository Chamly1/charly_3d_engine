#ifndef LEARN_OPENGL_MESH_HPP
#define LEARN_OPENGL_MESH_HPP

#include "GL/glew.h"

class Mesh {
private:
    GLuint mVAO, mVBO, mIBO;
    GLsizei mIndexCount;

public:
    Mesh(GLfloat *vertices, unsigned int verticesNum, unsigned int *indices, unsigned int indicesNum);
    ~Mesh();

    void render();

    // delete implicit methods
    Mesh(Mesh const &) = delete;
    Mesh & operator = (Mesh const &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh & operator = (Mesh &&) = delete;
};

#endif //LEARN_OPENGL_MESH_HPP