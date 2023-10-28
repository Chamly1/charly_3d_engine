#ifndef CHARLY_3D_ENGINE_OPENGLUTILS_HPP
#define CHARLY_3D_ENGINE_OPENGLUTILS_HPP

#include "Logger.hpp"

#include "gl/glew.h"

#define GL_CALL(func)                                                                                                  \
    while (glGetError() != GL_NO_ERROR);                                                                               \
    func;                                                                                                              \
    while (GLenum error = glGetError()) {                                                                              \
        LOG_ERROR("OpenGL: 0x%x", error)                                                                               \
    }                                                                                                                  \

namespace Charly {



}

#endif //CHARLY_3D_ENGINE_OPENGLUTILS_HPP
