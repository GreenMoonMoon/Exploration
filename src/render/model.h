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
    unsigned int ebo;
    unsigned int program;
    int vertexCount;
    int elementCount;
    int tintUniformLocation;

public:
    Mesh() {
        float vertices[] = {
                0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f   // top left
        };
        unsigned int indices[] = {  // note that we start from 0!
                0, 1, 3,  // first Triangle
                1, 2, 3   // second Triangle
        };

        vertexCount = 4;
        elementCount = 6;

        //Generate buffers
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);
        glGenVertexArrays(1, &vao);

        glBindVertexArray(vao); //Bind vertex array buffer

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, GL_STATIC_DRAW);

        //Set the attribute in the glsl
        //Setup layout(location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (int) sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
        //Setup layout(location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * (int) sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        //Unbind buffers
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Draw() const {
        glUseProgram(program);
        glUniform3f(tintUniformLocation, 0.0f, 1.0f, 0.0f);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
};

#endif //EXPLORATION_MODEL_H
