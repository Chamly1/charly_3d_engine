cmake_minimum_required(VERSION 3.24)
project(learn_OpenGL)

set(CMAKE_CXX_STANDARD 17)

add_executable(learn_OpenGL)

# link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(learn_OpenGL opengl32)

# link GLEW
add_compile_definitions(GLEW_STATIC)
include_directories(external/glew-2.1.0/include)
set(GLEW_LIB_DIR ${PROJECT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64)
target_link_libraries(learn_OpenGL ${GLEW_LIB_DIR}/glew32s.lib)

# link GLFW
include_directories(external/glfw-3.3.8/include)
set(GLFW_LIB_DIR ${PROJECT_SOURCE_DIR}/external/glfw-3.3.8/lib-vc2019)
target_link_libraries(learn_OpenGL ${GLFW_LIB_DIR}/glfw3.lib)

include_directories(src/include)
add_subdirectory(src/cpp)

target_link_libraries(learn_OpenGL main_obj_lib)
