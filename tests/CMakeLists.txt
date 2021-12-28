project(ExplorationTests CXX)
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(gtest)

add_executable(TestsMap map_tests.cpp ../src/map.c)
target_link_libraries(TestsMap gtest gtest_main raylib)

add_executable(TestsBasicPhysic basic_physic_tests.cpp ../src/physic/particles.c)
target_link_libraries(TestsBasicPhysic gtest gtest_main raylib)