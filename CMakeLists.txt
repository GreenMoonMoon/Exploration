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

set(
        RenderExpl1_SOURCE_FILES
        render_exploration1.cpp

        src/render/shader.cpp
        src/render/model.cpp

        external/glad/src/gl.c
)

add_executable(RenderExpl1 ${RenderExpl1_SOURCE_FILES})
target_include_directories(RenderExpl1 PUBLIC "external/glad/include")
target_link_libraries(RenderExpl1 glfw)

set(
        RenderExpl2_SOURCE_FILES
        render_exploration2.cpp

        src/render/shader.cpp
        src/render/model.cpp

        external/glad/src/gl.c
)

add_executable(RenderExpl2 ${RenderExpl2_SOURCE_FILES})
target_include_directories(RenderExpl2 PUBLIC "external/glad/include")
target_link_libraries(RenderExpl2 glfw)

add_executable(PhysicExpl1 physic_exploration1.cpp src/physic/particles.cpp)
target_link_libraries(PhysicExpl1 raylib)

#TESTS
add_subdirectory(tests)