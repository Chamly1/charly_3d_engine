#include "ModelLoader.hpp"
#include "Logger.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Charly {

    float* ModelLoader::mVerticesBuffer = nullptr;
    unsigned int ModelLoader::mVerticesBufferSize = 0;
    unsigned int ModelLoader::mVerticesBufferIndex = 0;

    unsigned int* ModelLoader::mIndicesBuffer = nullptr;
    unsigned int ModelLoader::mIndicesBufferSize = 0;
    unsigned int ModelLoader::mIndicesBufferIndex = 0;

    void ModelLoader::processAssimpNode(aiNode *node, const aiScene *scene) {
        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            processAssimpMesh(scene->mMeshes[node->mMeshes[i]], scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processAssimpNode(node->mChildren[i], scene);
        }
    }

    void ModelLoader::processAssimpMesh(aiMesh *mesh, const aiScene *scene) {
        /******************Vertices******************/
        mVerticesBufferSize = mVerticesBufferSize + mesh->mNumVertices * (3 + 3) * sizeof(float);
        mVerticesBuffer = (float*)realloc(mVerticesBuffer, mVerticesBufferSize);

        unsigned int mIndicesShift = mVerticesBufferIndex / (3 + 3);
        for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
            mVerticesBuffer[mVerticesBufferIndex++] = mesh->mVertices[i].x;
            mVerticesBuffer[mVerticesBufferIndex++] = mesh->mVertices[i].y;
            mVerticesBuffer[mVerticesBufferIndex++] = mesh->mVertices[i].z;

            // aiProcess_GenNormals guarantees that there will be normals
            mVerticesBuffer[mVerticesBufferIndex++] = mesh->mNormals[i].x;
            mVerticesBuffer[mVerticesBufferIndex++] = mesh->mNormals[i].y;
            mVerticesBuffer[mVerticesBufferIndex++] = mesh->mNormals[i].z;
        }

        /******************Indices******************/
        mIndicesBufferSize = mIndicesBufferSize + mesh->mNumFaces * 3 * sizeof(unsigned int);
        mIndicesBuffer = (unsigned int*)realloc(mIndicesBuffer, mIndicesBufferSize);

        for(unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            // aiProcess_Triangulate guarantees that face will have 3 vertices
            mIndicesBuffer[mIndicesBufferIndex++] = mesh->mFaces[i].mIndices[0] + mIndicesShift;
            mIndicesBuffer[mIndicesBufferIndex++] = mesh->mFaces[i].mIndices[1] + mIndicesShift;
            mIndicesBuffer[mIndicesBufferIndex++] = mesh->mFaces[i].mIndices[2] + mIndicesShift;
        }
    }

    std::shared_ptr<VertexArray> ModelLoader::loadVertexArray(const char* modelPath) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            LOG_ERROR("ASSIMP: %s", importer.GetErrorString())
        }

        mVerticesBuffer = NULL;
        mIndicesBuffer = NULL;

        mVerticesBufferSize = 0;
        mIndicesBufferSize = 0;

        mVerticesBufferIndex = 0;
        mIndicesBufferIndex = 0;

        processAssimpNode(scene->mRootNode, scene);

        BufferLayout bufferLayout = {
                {ShaderDataType::Float3, "pos"},
                {ShaderDataType::Float3, "normal"}
        };
        std::shared_ptr<VertexBuffer> vertexBuffer = std::make_shared<VertexBuffer>(mVerticesBuffer, mVerticesBufferSize);
        std::shared_ptr<IndexBuffer> indexBuffer = std::make_shared<IndexBuffer>(mIndicesBuffer, mIndicesBufferSize / sizeof(unsigned int));
        std::shared_ptr<VertexArray> vertexArray = std::make_shared<VertexArray>(vertexBuffer, indexBuffer, bufferLayout);

        free(mVerticesBuffer);
        free(mIndicesBuffer);
        mVerticesBuffer = NULL;
        mIndicesBuffer = NULL;

        return vertexArray;
    }

}
