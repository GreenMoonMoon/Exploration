cmake_minimum_required(VERSION 3.21)
project(Exploration C)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/GreenMoonMoon/raylib.git
        #        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.0.0)
Set(GRAPHICS "GRAPHICS_API_OPENGL_43")
FetchContent_MakeAvailable(raylib)

set(CMAKE_C_STANDARD 17)

add_executable(Exploration main.c)
target_link_libraries(Exploration raylib)

add_executable(ChunkEditor chunk_editor.c src/map.c)
target_link_libraries(ChunkEditor raylib)

#DEBUG
add_executable(MeshInstanced mesh_instanced.c)
target_link_libraries(MeshInstanced raylib)

#TESTS
add_subdirectory(tests)