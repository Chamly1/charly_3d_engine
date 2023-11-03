include_directories(include)

add_compile_definitions(ENABLE_LOGGING)

add_library(main_obj_lib OBJECT
        cpp/Model.cpp
        cpp/Material.cpp
        cpp/Logger.cpp
        cpp/Text.cpp
        cpp/GlyphAtlas.cpp
        cpp/Font.cpp
        cpp/VertexArray.cpp
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