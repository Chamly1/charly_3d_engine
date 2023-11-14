#ifndef CHARLY_3D_ENGINE_MODELLOADER_HPP
#define CHARLY_3D_ENGINE_MODELLOADER_HPP

#include "VertexArray.hpp"

#include "assimp/scene.h"

namespace Charly {

    class ModelLoader {
    private:
        static float *mVerticesBuffer;
        static unsigned int mVerticesBufferSize;
        static unsigned int mVerticesBufferIndex;

        static unsigned int *mIndicesBuffer;
        static unsigned int mIndicesBufferSize;
        static unsigned int mIndicesBufferIndex;

        static void processAssimpNode(aiNode *node, const aiScene *scene);
        static void processAssimpMesh(aiMesh *mesh, const aiScene *scene);

        ModelLoader() {}
        ~ModelLoader() {}

    public:
        static std::shared_ptr<VertexArray> loadVertexArray(const char* modelPath);

    };

}

#endif //CHARLY_3D_ENGINE_MODELLOADER_HPP
