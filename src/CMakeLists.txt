include_directories(include)

add_library(main_obj_lib OBJECT
        cpp/IndexBuffer.cpp
        cpp/VertexBuffer.cpp
        cpp/Texture.cpp
        cpp/Camera.cpp
        cpp/GLFWinputHandler.cpp
        cpp/OpenGLapp.cpp
        cpp/Mesh.cpp
        cpp/Shader.cpp
        cpp/utils.cpp
        cpp/main.cpp)