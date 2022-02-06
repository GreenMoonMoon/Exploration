//
// Created by MoonMoon on 2022-01-20.
//
#include <vector>

#include "render/shader.h"
#include "resource.h"

#ifndef EXPLORATION_MODEL_H
#define EXPLORATION_MODEL_H

namespace Expl {
    struct MeshResource : Resource {
        MeshResource();
        explicit MeshResource(const char* filePath);
        MeshResource(std::initializer_list<float> inVertices, std::initializer_list<unsigned int> inIndices);
        MeshResource(std::vector<float> inVertices, std::vector<unsigned int> inIndices);

        std::vector<float> vertices{};
        std::vector<unsigned int> indices{};

        void Serialize() override;
        void Deserialize() override;

        //Built-in geometries
        static MeshResource Quad(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        [[maybe_unused]] static MeshResource Cube(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    };
}

#endif //EXPLORATION_MODEL_H
