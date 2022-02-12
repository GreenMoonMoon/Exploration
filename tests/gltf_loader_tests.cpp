//
// Created by MoonMoon on 2022-01-29.
//

#include "gtest/gtest.h"
#include "../src/loader/model.h"
#include

using namespace Expl;


auto test_file = "C:/Users/josue/CLionProjects/PhysicExploration/resources/models/suzanne.gltf";

TEST(ReadFile, LoadingFile) {
    GLTFLoader loader;
    loader.LoadFile(test_file);
}

TEST(ReadFile, LoadMeshFromFile) {
    GLTFLoader loader;
    loader.LoadFile(test_file);

    Mesh mesh = loader.GetMesh(0);
    EXPECT_STREQ(mesh.name, "suzanne");
}