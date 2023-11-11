#include "Model.hpp"
#include "Renderer.hpp"
#include "Logger.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

namespace Charly {

    void Model::processAssimpNode(aiNode *node, const aiScene *scene) {

        for (unsigned int i = 0; i < node->mNumMeshes; i++) {
            processAssimpMesh(scene->mMeshes[node->mMeshes[i]], scene);
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++) {
            processAssimpNode(node->mChildren[i], scene);
        }
    }

    void Model::processAssimpMesh(aiMesh *mesh, const aiScene *scene) {

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

    void Model::draw(Renderer& renderer) const {
        mMaterial->bind();

        mShader->bind();
        mShader->uploadUniformMatrix4f("u_Model", calculateModelMatrix());
        mShader->uploadUniformMatrix4f("u_Projection", renderer.getProjectionMatrix());
        mShader->uploadUniformMatrix4f("u_View", renderer.getViewMatrix());
        mShader->uploadUniformMatrix4f("u_NormalRotation", calculateRotationMatrix());

        mShader->uploadUniform3f("u_Color", mMaterial->getColor());
        mShader->uploadUniform3f("u_LightColor", renderer.getPointLight().color);
        mShader->uploadUniform3f("u_LightPos", renderer.getPointLight().position);
        mShader->uploadUniform3f("u_AmbientLightColor", renderer.getAmbientLight().color);
        mShader->uploadUniform1f("u_AmbientLightStrength", renderer.getAmbientLight().strength);

        mVertexArray->draw();
    }

    Model::Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material)
    : mVertexArray(vertexArray)
    , mShader(shader)
    , mMaterial(material) {

    }

    Model::Model(const char* modelPath, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material)
    : mShader(shader)
    , mMaterial(material) {

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
        mVertexArray = std::make_shared<VertexArray>(vertexBuffer, indexBuffer, bufferLayout);

        free(mVerticesBuffer);
        free(mIndicesBuffer);
        mVerticesBuffer = NULL;
        mIndicesBuffer = NULL;
    }

}
