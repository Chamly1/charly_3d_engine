cmake_minimum_required(VERSION 3.24)
project(charly_3d_engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(charly_3d_engine)

# link OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(charly_3d_engine opengl32)

# link GLEW
add_compile_definitions(GLEW_STATIC)
include_directories(external/glew-2.1.0/include)
set(GLEW_LIB_DIR ${PROJECT_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64)
target_link_libraries(charly_3d_engine ${GLEW_LIB_DIR}/glew32s.lib)

# link GLFW
include_directories(external/glfw-3.3.8/include)
set(GLFW_LIB_DIR ${PROJECT_SOURCE_DIR}/external/glfw-3.3.8/lib-vc2019)
target_link_libraries(charly_3d_engine ${GLFW_LIB_DIR}/glfw3.lib)

# link GLM
include_directories(external/glm-0.9.9.8)

# link STB
include_directories(external/stb)

# link Assimp
# assimp settings to reduce size to be able to load debug version to GitHub (< 100mb)
#-- Enabled exporter formats: OBJ COLLADA FBX
#-- Enabled importer formats: COLLADA OBJ FBX
# for debug version set /O1 to reduce size and disable /RTC1 to avoid conflict with /O1 flag
include_directories(external/Assimp-5.2.4/include)
set(ASSIMP_LIB_DIR ${PROJECT_SOURCE_DIR}/external/Assimp-5.2.4/lib)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(charly_3d_engine ${ASSIMP_LIB_DIR}/debug/zlibstaticd.lib)
    target_link_libraries(charly_3d_engine ${ASSIMP_LIB_DIR}/debug/assimp-vc142-mtd.lib)
else()
    target_link_libraries(charly_3d_engine ${ASSIMP_LIB_DIR}/release/zlibstatic.lib)
    target_link_libraries(charly_3d_engine ${ASSIMP_LIB_DIR}/release/assimp-vc142-mt.lib)
endif()

include_directories(src/include)
add_subdirectory(src)

target_link_libraries(charly_3d_engine main_obj_lib)

# copy resources
add_custom_command(TARGET charly_3d_engine
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resources
        ${PROJECT_BINARY_DIR}/resources)
