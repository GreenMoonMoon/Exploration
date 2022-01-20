//
// Created by MoonMoon on 2022-01-20.
//
#include "glad/gl.h"

#ifndef EXPLORATION_MODEL_H
#define EXPLORATION_MODEL_H

class Mesh {
public:
    unsigned int vbo;
    unsigned int vao;
    unsigned int program;
    int vertexCount;

public:
    Mesh() {
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, // left
                0.5f, -0.5f, 0.0f, // right
                0.0f,  0.5f, 0.0f  // top
        };

        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        //Set the attribute in the glsl
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); //Setup layout(location = 0)
        glEnableVertexAttribArray(0);
    }

    void Draw() const {
        glUseProgram(program);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    }
};

#endif //EXPLORATION_MODEL_H
