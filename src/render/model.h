//
// Created by MoonMoon on 2022-01-20.
//
#include "glad/gl.h"
#include "shader.h"

#ifndef EXPLORATION_MODEL_H
#define EXPLORATION_MODEL_H

namespace Expl {
    class Mesh {
    public:
        unsigned int vbo;
        unsigned int vao;
        unsigned int ebo;
        unsigned int program;
        int vertexCount;
        int elementCount;

        Shader material;

    public:
        Mesh();

        void Draw() const;

        void SetMaterial(Shader material);
    };

}

#endif //EXPLORATION_MODEL_H
