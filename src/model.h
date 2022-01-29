//
// Created by MoonMoon on 2022-01-20.
//
#include "glad/gl.h"
#include "render/shader.h"

#ifndef EXPLORATION_MODEL_H
#define EXPLORATION_MODEL_H

namespace Expl {
    class Mesh {
    public:
        unsigned int VBO;
        unsigned int VAO;
        unsigned int EBO;
        int ElementCount;
        int VertexCount;
        int Mode;

    public:
        Mesh();
    };

    Mesh LoadMesh(const char* filePath);
}

#endif //EXPLORATION_MODEL_H
