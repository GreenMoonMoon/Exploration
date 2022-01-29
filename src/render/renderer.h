//
// Created by MoonMoon on 2022-01-29.
//

#include "glad/gl.h"
#include "../model.h"

#ifndef EXPLORATION_RENDERER_H
#define EXPLORATION_RENDERER_H

namespace Expl {

    class Renderer {
    public:
        void DrawMesh(Mesh &mesh, Shader &shader) {
            shader.Use();
            shader.SetVectorUniform("tint", 0.0f, 1.0f, 0.0f);

            glBindVertexArray(mesh.VAO);
            glDrawElements(mesh.Mode, mesh.ElementCount, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
    };
}

#endif //EXPLORATION_RENDERER_H
