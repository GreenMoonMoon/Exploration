cmake_minimum_required(VERSION 3.21)
project(Exploration CXX)

include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/GreenMoonMoon/raylib.git
        #        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 4.0.0)
Set(GRAPHICS "GRAPHICS_API_OPENGL_43")
FetchContent_MakeAvailable(raylib)

set(CMAKE_CXX_STANDARD 20)

add_executable(Expl1 exploration1.cpp src/physic/particles.cpp)
target_link_libraries(Expl1 raylib)

add_executable(Expl2 exploration2.cpp src/map.cpp)
target_link_libraries(Expl2 raylib)

add_executable(Expl3 exploration3.cpp)
target_link_libraries(Expl3 raylib)

add_executable(Expl4 exploration4.cpp)
target_link_libraries(Expl4 raylib)

add_executable(PhysicExpl1 physic_exploration1.cpp src/physic/particles.cpp)
target_link_libraries(PhysicExpl1 raylib)

#TESTS
add_subdirectory(tests)