#ifndef CHARLY_3D_ENGINE_MODEL_HPP
#define CHARLY_3D_ENGINE_MODEL_HPP

#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "Drawable.hpp"
#include "Transformable.hpp"

#include "assimp/scene.h"

namespace Charly {

    class Model : public Transformable, public Drawable {
    private:
        std::shared_ptr<VertexArray> mVertexArray;
        std::shared_ptr<Shader> mShader;
        std::shared_ptr<Material> mMaterial;

        float *mVerticesBuffer;
        unsigned int mVerticesBufferSize;
        unsigned int mVerticesBufferIndex;
        unsigned int *mIndicesBuffer;
        unsigned int mIndicesBufferSize;
        unsigned int mIndicesBufferIndex;

        void processAssimpNode(aiNode *node, const aiScene *scene);
        void processAssimpMesh(aiMesh *mesh, const aiScene *scene);

    protected:
        void draw(Renderer& renderer) const override;

    public:
        Model(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material);
        Model(const char* modelPath, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Material>& material);

        // delete implicit methods
        Model(Model const &) = delete;
        Model & operator = (Model const &) = delete;
        Model(Model &&) = delete;
        Model & operator = (Model &&) = delete;
    };

}

#endif //CHARLY_3D_ENGINE_MODEL_HPP
