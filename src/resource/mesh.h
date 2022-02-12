//
// Created by MoonMoon on 2022-02-11.
//
#include <vector>

#include "resource.h"

#ifndef EXPLORATION_MESH_H
#define EXPLORATION_MESH_H

namespace Expl {
    struct MeshResource : Resource {
        std::vector<float> vertices{};
        std::vector<unsigned int> indices{};

        MeshResource(std::initializer_list<float> vertices_, std::initializer_list<unsigned int> indices_);

        MeshResource(std::vector<float> vertices_, std::vector<unsigned int> indices_);

        void Serialize(const std::filesystem::path &path) override;

        void Deserialize(const std::filesystem::path &path) override;

        //Built-in geometries
        [[maybe_unused]] static MeshResource Quad(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        [[maybe_unused]] static MeshResource Cube(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    };

    class MeshLoader : public ResourceLoader {
        void Load(const std::filesystem::path &path) override;
    };
}

#endif //EXPLORATION_MESH_H
