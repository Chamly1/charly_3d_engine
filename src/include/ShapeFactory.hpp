#ifndef CHARLY_3D_ENGINE_SHAPEFACTORY_HPP
#define CHARLY_3D_ENGINE_SHAPEFACTORY_HPP

#include "VertexArray.hpp"

#include <memory>

namespace Charly {

    class ShapeFactory {
    private:
        ShapeFactory() {}
        ~ShapeFactory() {}

    public:
        static std::shared_ptr<VertexArray> createCube();
        static std::shared_ptr<VertexArray> createSquare();
        static std::shared_ptr<VertexArray> createIcoSphere(int subdivisions);

    };

}

#endif //CHARLY_3D_ENGINE_SHAPEFACTORY_HPP
