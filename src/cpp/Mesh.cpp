#include "Mesh.hpp"

Mesh::Mesh(GLfloat *vertices, unsigned int verticesNum, unsigned int *indices, unsigned int indicesNum, bool includeUVCoordinate) {
    mIndexCount = indicesNum;

    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    glGenBuffers(1, &mIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indicesNum, indices, GL_STATIC_DRAW);

    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticesNum, vertices, GL_STATIC_DRAW);

    if (includeUVCoordinate) {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, 0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, reinterpret_cast<void*>(sizeof(vertices[0]) * 3));
        glEnableVertexAttribArray(1);
    } else {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    A VAO stores the glBindBuffer calls when the target is GL_ELEMENT_ARRAY_BUFFER. This
//    also means it stores its unbind calls so make sure you don't unbind the element array buffer before
//    unbinding your VAO, otherwise it doesn't have an IBO configured.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &mIBO);
    glDeleteBuffers(1, &mVBO);
    glDeleteVertexArrays(1, &mVAO);
}

void Mesh::render() {
    glBindVertexArray(mVAO);
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
