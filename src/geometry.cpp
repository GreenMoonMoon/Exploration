//
// Created by MoonMoon on 2022-01-23.
//
#include <iostream>

#include "glad/gl.h"
#include "geometry.h"

namespace Expl {
    MeshResource::MeshResource(const char *filePath) {
        path = filePath;
    }

    MeshResource::MeshResource(std::initializer_list<float> inVertices, std::initializer_list<unsigned int> inIndices)
            : vertices(inVertices), indices(inIndices) {}

    MeshResource::MeshResource(std::vector<float> inVertices, std::vector<unsigned int> inIndices) {
        vertices = std::move(inVertices);
        indices = std::move(inIndices);
    }

    void MeshResource::Serialize() {
        if (!path) return;
        std::ofstream out;
        out.open(path, std::ios::binary);
        if (!out.is_open()) return;
        size_t counts[2] = {vertices.size(), indices.size()};

        out.write(reinterpret_cast<char *>(counts), 2 * sizeof(size_t));
        out.write(reinterpret_cast<char *>(vertices.data()),
                  static_cast<std::streamsize>(vertices.size() * sizeof(float)));
        out.write(reinterpret_cast<char *>(indices.data()), static_cast<std::streamsize>(indices.size() * sizeof(int)));

        out.close();
    }

    void MeshResource::Deserialize() {
        if (!path) return;
        std::ifstream in;
        in.open(path, std::ios::binary);
        if (!in.is_open()) return;

        size_t counts[2];
        in.read(reinterpret_cast<char *>(&counts), 2 * sizeof(size_t));


        vertices.resize(counts[0]);
        indices.resize(counts[1]);

        in.read(reinterpret_cast<char *>(vertices.data()), static_cast<std::streamsize>(counts[0] * sizeof(float)));
        in.read(reinterpret_cast<char *>(indices.data()), static_cast<std::streamsize>(counts[1] * sizeof(int)));

        std::cout << "vertex count: " << counts[0] << "\n{";
        for (float vertex: vertices)
            std::cout << ' ' << vertex;
        std::cout << "}\n";

        std::cout << "index count: " << counts[1] << "\n{";
        for (unsigned int index: indices)
            std::cout << ' ' << index;
        std::cout << "}\n";
    }

    //Built-in geometries
    [[maybe_unused]] MeshResource MeshResource::Quad(float x, float y, float z) {
        return MeshResource(
                {
                        -1.0f + x, -1.0f + y, 0.0f + z, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                        -1.0f + x, 1.0f + y, 0.0f + z, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
                        1.0f + x, 1.0f + y, 0.0f + z, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
                        1.0f + x, -1.0f + y, 0.0f + z, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f
                },
                {0, 1, 2, 2, 3, 0}
        );
    };

    [[maybe_unused]] MeshResource MeshResource::Cube(float x, float y, float z) {
        return MeshResource(
                {
                        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // top right
                        1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom right
                        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, // bottom left
                        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, // top left
                        1.0f, 0.0f, 1.0, 0.0f, 0.0f, 0.0f
                },
                {
                        0, 1, 3, 1, 2, 3
                });
    }
}