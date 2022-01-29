project(ExplorationTests CXX)
set(CMAKE_CXX_STANDARD 20)

FetchContent_Declare(
        gtest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(gtest)


add_executable(TestBasicPhysic basic_physic_tests.cpp ../src/physic/particles.cpp)
target_link_libraries(TestBasicPhysic gtest gtest_main raylib)

add_executable(TestParticles particles_tests.cpp ../src/physic/particles.cpp)
target_link_libraries(TestParticles gtest gtest_main raylib)

add_executable(TestExplMath expl_math_tests.cpp)
target_link_libraries(TestExplMath gtest gtest_main)

add_executable(TestGLTFLoader gltf_loader_tests.cpp)
target_include_directories(TestGLTFLoader PUBLIC ${tinygltf_SOURCE_DIR})
target_link_libraries(TestGLTFLoader gtest gtest_main)