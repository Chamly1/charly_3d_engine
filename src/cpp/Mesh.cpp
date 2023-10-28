#include "Mesh.hpp"
#include "OpenGLUtils.hpp"

namespace Charly {

    Mesh::Mesh(GLfloat *vertices, unsigned int verticesNum, unsigned int *indices, unsigned int indicesNum, bool includeUVCoordinate) {
        mIndexCount = indicesNum;

        GL_CALL(glGenVertexArrays(1, &mVAO))
        GL_CALL(glBindVertexArray(mVAO))

        GL_CALL(glGenBuffers(1, &mIBO))
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO))
        GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesNum, indices, GL_STATIC_DRAW))

        GL_CALL(glGenBuffers(1, &mVBO))
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, mVBO))
        GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesNum, vertices, GL_STATIC_DRAW))

        if (includeUVCoordinate) {
            GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0))
            GL_CALL(glEnableVertexAttribArray(0))
            GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, reinterpret_cast<void*>(sizeof(vertices[0]) * 3)))
            GL_CALL(glEnableVertexAttribArray(1))
        } else {
            GL_CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0))
            GL_CALL(glEnableVertexAttribArray(0))
        }

        GL_CALL(glBindVertexArray(0))
        GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0))
//    A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. This
//    also means it stores its unbind calls so make sure you don't unbind the element array buffer before
//    unbinding your VAO, otherwise it doesn't have an IBO configured.
        GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
    }

    Mesh::~Mesh() {
        GL_CALL(glDeleteBuffers(1, &mIBO))
        GL_CALL(glDeleteBuffers(1, &mVBO))
        GL_CALL(glDeleteVertexArrays(1, &mVAO))
    }

    void Mesh::render() {
        GL_CALL(glBindVertexArray(mVAO))
        GL_CALL(glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0))
        GL_CALL(glBindVertexArray(0))
    }

}
