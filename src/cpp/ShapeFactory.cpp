#include "ShapeFactory.hpp"
#include "Logger.hpp"

#include "glm/glm.hpp"

namespace Charly {

    GLfloat cubeVertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    GLfloat squareVertices[] = {
            -0.5f,  0.0f, -0.5f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.0f, -0.5f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.0f,  0.5f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.0f,  0.5f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.0f,  0.5f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.0f, -0.5f,  0.0f,  1.0f, 0.0f
    };
    BufferLayout shapeBufferLayout = {
            {ShaderDataType::Float3, "pos"},
            {ShaderDataType::Float3, "normal"}
    };
    
    std::shared_ptr<VertexArray> ShapeFactory::createCube() {
        std::shared_ptr<VertexBuffer> cubeVertexBuffer = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices));
        return std::make_shared<VertexArray>(cubeVertexBuffer, shapeBufferLayout);
    }

    std::shared_ptr<VertexArray> ShapeFactory::createSquare() {
        std::shared_ptr<VertexBuffer> squareVertexBuffer = std::make_shared<VertexBuffer>(squareVertices, sizeof(squareVertices));
        return std::make_shared<VertexArray>(squareVertexBuffer, shapeBufferLayout);
    }


    /**
     * Generate a vertex between two points in icosphere and correct vertex's magnitude to be 0.5(icosphere radius).
     * Add this new vertex to icosphereVertices and return it's index.
     *
     * @param icosphereVertices icosphere vertices.
     * @param vertexIndex1 index of first vertex.
     * @param vertexIndex2 index of second vertex.
     *
     * @return index of the middle vertex in icosphereVertices.
     */
    static int addMiddlePoint(std::vector<glm::vec3>& icosphereVertices, int vertexIndex1, int vertexIndex2) {
        glm::vec3 middleVertex((icosphereVertices[vertexIndex1].x + icosphereVertices[vertexIndex2].x) / 2.f,
                               (icosphereVertices[vertexIndex1].y + icosphereVertices[vertexIndex2].y) / 2.f,
                               (icosphereVertices[vertexIndex1].z + icosphereVertices[vertexIndex2].z) / 2.f);

        // change the vertex position to lay on sphere (in our case with radius 0.5)
        float magnitude = sqrt(middleVertex.x * middleVertex.x + middleVertex.y * middleVertex.y + middleVertex.z * middleVertex.z);
        middleVertex /= magnitude;
        middleVertex *= 0.5f;

        icosphereVertices.push_back(middleVertex);
        return icosphereVertices.size() - 1;
    }

    //TODO optimize code 
    std::shared_ptr<VertexArray> ShapeFactory::createIcoSphere(int subdivisions) {

        if (subdivisions < 0) {
            LOG_ERROR("IcoSphere subdivisions must be greater or equal to 0. Passed value is: %d", subdivisions)
        }

        // To create icosahedron we need golden rectangles. Golden rectangle is a rectangle whose side lengths are in
        // the golden ratio, 1 : phi (phi = 1.618... or (1+sqrt(5))/2 )
        // Because we want to create icosphere with diameter 1, we need golden rectangle with diagonal 1. According to
        // Pythagorean theorem 1^2 = (1*x)^2 + (phi*x)^2 => x = sqrt(4.f / (10.f + 2.f * sqrt(5.f)))
        float phi = (1.f + sqrt(5.f)) / 2.f;
        float x = sqrt(4.f / (10.f + 2.f * sqrt(5.f)));

        // to locate our icosahedron at the center of coordinate system we need divide our golden rectangle sides by 2
        float b = (x * phi) / 2.f;
        float a = x / 2.f;

        std::vector<glm::vec3> icosahedronVertices;

        icosahedronVertices.push_back(glm::vec3(-a,  b, 0));
        icosahedronVertices.push_back(glm::vec3( a,  b, 0));
        icosahedronVertices.push_back(glm::vec3(-a, -b, 0));
        icosahedronVertices.push_back(glm::vec3( a, -b, 0));

        icosahedronVertices.push_back(glm::vec3(0, -a,  b));
        icosahedronVertices.push_back(glm::vec3(0,  a,  b));
        icosahedronVertices.push_back(glm::vec3(0, -a, -b));
        icosahedronVertices.push_back(glm::vec3(0,  a, -b));

        icosahedronVertices.push_back(glm::vec3( b, 0, -a));
        icosahedronVertices.push_back(glm::vec3( b, 0,  a));
        icosahedronVertices.push_back(glm::vec3(-b, 0, -a));
        icosahedronVertices.push_back(glm::vec3(-b, 0,  a));

        std::vector<glm::ivec3> icosahedronFaces;

        icosahedronFaces.push_back(glm::ivec3());

        // 5 faces around point 0
        icosahedronFaces.push_back(glm::ivec3(0, 11, 5));
        icosahedronFaces.push_back(glm::ivec3(0, 5, 1));
        icosahedronFaces.push_back(glm::ivec3(0, 1, 7));
        icosahedronFaces.push_back(glm::ivec3(0, 7, 10));
        icosahedronFaces.push_back(glm::ivec3(0, 10, 11));

        // 5 adjacent faces
        icosahedronFaces.push_back(glm::ivec3(1, 5, 9));
        icosahedronFaces.push_back(glm::ivec3(5, 11, 4));
        icosahedronFaces.push_back(glm::ivec3(11, 10, 2));
        icosahedronFaces.push_back(glm::ivec3(10, 7, 6));
        icosahedronFaces.push_back(glm::ivec3(7, 1, 8));

        // 5 faces around point 3
        icosahedronFaces.push_back(glm::ivec3(3, 9, 4));
        icosahedronFaces.push_back(glm::ivec3(3, 4, 2));
        icosahedronFaces.push_back(glm::ivec3(3, 2, 6));
        icosahedronFaces.push_back(glm::ivec3(3, 6, 8));
        icosahedronFaces.push_back(glm::ivec3(3, 8, 9));

        // 5 adjacent faces
        icosahedronFaces.push_back(glm::ivec3(4, 9, 5));
        icosahedronFaces.push_back(glm::ivec3(2, 4, 11));
        icosahedronFaces.push_back(glm::ivec3(6, 2, 10));
        icosahedronFaces.push_back(glm::ivec3(8, 6, 7));
        icosahedronFaces.push_back(glm::ivec3(9, 8, 1));

        // subdivide icosahedron
        std::vector<glm::ivec3> icosahedronFaces2;
        for (int i = 0; i < subdivisions; i++) {
            for (glm::ivec3 face : icosahedronFaces) {

                int index1 = addMiddlePoint(icosahedronVertices, face.x, face.y);
                int index2 = addMiddlePoint(icosahedronVertices, face.y, face.z);
                int index3 = addMiddlePoint(icosahedronVertices, face.z, face.x);

                icosahedronFaces2.push_back(glm::ivec3(face.x, index1, index3));
                icosahedronFaces2.push_back(glm::ivec3(face.y, index1, index2));
                icosahedronFaces2.push_back(glm::ivec3(face.z, index2, index3));
                icosahedronFaces2.push_back(glm::ivec3(index1, index2, index3));

            }
            icosahedronFaces = std::move(icosahedronFaces2);
            icosahedronFaces2.clear();
        }

        // create vertex buffer
        // faces count * vertices per face * (coordinates per vertex + normal coordinates per vertex)
        unsigned int icoSphereVerticesBufferCount = icosahedronFaces.size() * 3 * (3 + 3);
        unsigned int icoSphereVerticesBufferSize = icoSphereVerticesBufferCount * sizeof(float);
        float* icoSphereVerticesBuffer = (float*)malloc(icoSphereVerticesBufferSize);

        unsigned int icoSphereVerticesBufferIndex = 0;
        glm::vec3 vector1, vector2, normal;
        for (unsigned int i = 0; i < icosahedronFaces.size(); i++) {

            // calculate normal vector
            glm::vec3 vector1 = icosahedronVertices[icosahedronFaces[i].y] - icosahedronVertices[icosahedronFaces[i].x];
            glm::vec3 vector2 = icosahedronVertices[icosahedronFaces[i].z] - icosahedronVertices[icosahedronFaces[i].x];
            glm::vec3 normal = glm::normalize(glm::cross(vector1, vector2));

            // vertex 1
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].x].x;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].x].y;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].x].z;
            // normal
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.x;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.y;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.z;

            // vertex 2
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].y].x;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].y].y;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].y].z;
            // normal
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.x;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.y;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.z;

            // vertex 3
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].z].x;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].z].y;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = icosahedronVertices[icosahedronFaces[i].z].z;
            // normal
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.x;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.y;
            icoSphereVerticesBuffer[icoSphereVerticesBufferIndex++] = normal.z;
        }

        std::shared_ptr<VertexBuffer> icoSphereVertexBuffer = std::make_shared<VertexBuffer>(icoSphereVerticesBuffer, icoSphereVerticesBufferSize);
        std::shared_ptr<VertexArray> icoSphereVertexArray = std::make_shared<VertexArray>(icoSphereVertexBuffer, shapeBufferLayout);

        free(icoSphereVerticesBuffer);
        return icoSphereVertexArray;
    }
    
}
