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

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
)
FetchContent_GetProperties(glm)
if (NOT glm_POPULATED)
    FetchContent_Populate(glm)
endif ()
add_subdirectory(${glm_SOURCE_DIR})

FetchContent_MakeAvailable(glfw)

set(CMAKE_CXX_STANDARD 20)

set(EXPL_SOURCE_FILES
        src/render/shader.cpp
        src/render/renderer.cpp
        src/render/gl_debug.cpp
        src/texture.cpp

        src/resource/mesh.cpp
        )

# Render Exploration 1
set(RenderExpl1_SOURCE_FILES
        render_exploration1.cpp

        ${EXPL_SOURCE_FILES}

        external/glad/src/gl.c
        )

add_executable(RenderExpl1 ${RenderExpl1_SOURCE_FILES})
target_include_directories(RenderExpl1 PUBLIC external/glad/include ${glm_SOURCE_DIR})
target_link_libraries(RenderExpl1 glfw)

# Render Exploration 2
set(RenderExpl2_SOURCE_FILES
        render_exploration2.cpp

        ${EXPL_SOURCE_FILES}

        external/glad/src/gl.c
        )

add_executable(RenderExpl2 ${RenderExpl2_SOURCE_FILES})
target_include_directories(RenderExpl2 PUBLIC external/glad/include ${glm_SOURCE_DIR})
target_link_libraries(RenderExpl2 glfw)

add_executable(PhysicExpl1 physic_exploration1.cpp src/physic/particles.cpp)
target_link_libraries(PhysicExpl1 raylib)

set(RessourceTool_SOURCE_FILES
        resource_tool.cpp

        external/glad/src/gl.c
        )
add_executable(RessourceTool ${RessourceTool_SOURCE_FILES})
target_include_directories(RessourceTool PUBLIC external/glad/include ${glm_SOURCE_DIR})
target_link_libraries(RessourceTool glfw)

#TESTS
add_subdirectory(tests)