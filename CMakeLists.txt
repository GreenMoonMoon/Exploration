cmake_minimum_required(VERSION 3.21)
project(Exploration C CXX)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.6
)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.86
)

FetchContent_MakeAvailable(glfw)

set(CMAKE_CXX_STANDARD 20)

add_executable(RenderExpl1 render_exploration1.cpp external/glad/src/gl.c)
target_include_directories(RenderExpl1 PUBLIC "external/glad/include")
target_link_libraries(RenderExpl1 glfw)

add_executable(PhysicExpl1 physic_exploration1.cpp src/physic/particles.cpp)
target_link_libraries(PhysicExpl1 raylib)

#TESTS
add_subdirectory(tests)