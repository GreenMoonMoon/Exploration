//
// Created by MoonMoon on 2022-01-29.
//

#include "glad/gl.h"
#include "../geometry.h"

#ifndef EXPLORATION_RENDERER_H
#define EXPLORATION_RENDERER_H

namespace Expl {
    struct Mesh {
        Resource* resource = nullptr;
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;
        int VertexCount = 0;
        int IndexCount = 0;
        int Mode = -1;
    };

    class Renderer {
    public:
        static Mesh LoadMeshResource(MeshResource &res) {
            //Generate buffers
            unsigned int vbo;
            unsigned int ebo;
            unsigned int vao;
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glGenVertexArrays(1, &vao);

            glBindVertexArray(vao); //Bind vertex array buffer

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(res.vertices.size() * sizeof(float)), res.vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(res.indices.size() * sizeof(int)), res.indices.data(), GL_STATIC_DRAW);

            //Set the attribute in the glsl
            //Setup layout(location = 0)
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (int) sizeof(float), nullptr);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);
//        //Setup layout(location = 1)
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * (int) sizeof(float), (void *) (3 * sizeof(float)));
//        glEnableVertexAttribArray(1);

            //Unbind buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            int mode = GL_TRIANGLES;
            return Mesh{
                    .resource = &res,
                    .VBO = vbo,
                    .VAO = vao,
                    .EBO = ebo,
                    .VertexCount = (int)res.vertices.size(),
                    .IndexCount = (int)res.indices.size(),
                    .Mode = mode
            };
        }

        static void DrawMesh(Mesh &mesh, Shader &shader) {
            shader.Use();
//            shader.SetVectorUniform("tint", 0.0f, 1.0f, 0.0f);

            glBindVertexArray(mesh.VAO);
            glDrawElements(mesh.Mode, mesh.IndexCount, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
    };
}

#endif //EXPLORATION_RENDERER_H
