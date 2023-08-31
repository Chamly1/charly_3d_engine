#ifndef CHAMLY_3D_ENGINE_BUFFERLAYOUT_HPP
#define CHAMLY_3D_ENGINE_BUFFERLAYOUT_HPP

#include "GL/glew.h"

#include <vector>
#include <string>

namespace Charly {

    enum class ShaderDataType {
        None,
        Float,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int,
        Int2,
        Int3,
        Int4,
        Bool
    };

    static unsigned int shaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }

        return 0;
    }

    GLenum shaderDataTypeToOpenGLBaseType(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:     return GL_FLOAT;
            case ShaderDataType::Float2:    return GL_FLOAT;
            case ShaderDataType::Float3:    return GL_FLOAT;
            case ShaderDataType::Float4:    return GL_FLOAT;
            case ShaderDataType::Mat3:      return GL_FLOAT;
            case ShaderDataType::Mat4:      return GL_FLOAT;
            case ShaderDataType::Int:       return GL_INT;
            case ShaderDataType::Int2:      return GL_INT;
            case ShaderDataType::Int3:      return GL_INT;
            case ShaderDataType::Int4:      return GL_INT;
            case ShaderDataType::Bool:      return GL_BOOL;
        }

        return 0;
    }

    unsigned int getshaderDataTypeElementCount(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Bool:      return 1;
        }

        return 0;
    }

    struct BufferElement {
        ShaderDataType type;
        std::string name;
        unsigned int size;
        unsigned int offset;
        bool normalized;

        BufferElement() {}
        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
                : type(type), name(name), size(shaderDataTypeSize(type)), offset(0), normalized(normalized) {

        }
    };

    class BufferLayout {
    private:
        std::vector<BufferElement> mElements;
        unsigned int mStride = 0;

        void calculateOffsetsAndStride() {
            unsigned int offset = 0;
            mStride = 0;
            for (auto& element : mElements) {
                element.offset = offset;
                offset += element.size;
                mStride += element.size;
            }
        }

    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& elements)
                : mElements(elements) {
            calculateOffsetsAndStride();
        }

        inline unsigned int getStride() const { return mStride; }
        inline const std::vector<BufferElement>& getElements() const { return mElements; }
    };

}

#endif //CHAMLY_3D_ENGINE_BUFFERLAYOUT_HPP
