include_directories(include)

add_library(main_obj_lib OBJECT
        cpp/OpenGLapp.cpp
        cpp/Mesh.cpp
        cpp/Shader.cpp
        cpp/utils.cpp
        cpp/main.cpp)