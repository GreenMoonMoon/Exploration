//
// Created by MoonMoon on 2022-01-20.
//
#include <vector>

#include "render/shader.h"
#include "resource.h"

#ifndef EXPLORATION_MODEL_H
#define EXPLORATION_MODEL_H

namespace Expl {
    struct MeshResource : public Resource {
        MeshResource(std::initializer_list<float> vertices, std::initializer_list<unsigned int> indices);

        std::vector<float> vertices{};
        std::vector<unsigned int> indices{};

        void Serialize() override;
        void Deserialize() override;
    };

    class Mesh {
    public:
        MeshResource res;
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        int ElementCount;
        int VertexCount;
        int Mode;

    public:
        Mesh();

        void LoadGL();
    };

    Mesh LoadMesh(const char *filePath);

}

#endif //EXPLORATION_MODEL_H
