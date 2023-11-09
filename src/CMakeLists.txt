include_directories(include)

add_compile_definitions(ENABLE_LOGGING)

add_library(main_obj_lib OBJECT
        cpp/Transformable.cpp
        cpp/LightSource.cpp
        cpp/Drawable.cpp
        cpp/Renderer.cpp
        cpp/Window.cpp
        cpp/PerformanceStatisticManager.cpp
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
        cpp/InputHandler.cpp
        cpp/OpenGLapp.cpp
        cpp/Mesh.cpp
        cpp/Shader.cpp
        cpp/utils.cpp
        cpp/main.cpp)