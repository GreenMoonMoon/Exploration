project(ExplorationTests CXX)
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(gtest)

add_executable(TestMap map_tests.cpp ../src/map.c)
target_link_libraries(TestMap gtest gtest_main raylib)

add_executable(TestBasicPhysic basic_physic_tests.cpp ../src/physic/particles.c)
target_link_libraries(TestBasicPhysic gtest gtest_main raylib)

add_executable(TestParticles particles_tests.cpp ../src/physic/particles.c)
target_link_libraries(TestParticles gtest gtest_main raylib)