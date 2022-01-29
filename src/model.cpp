//
// Created by MoonMoon on 2022-01-23.
//

#include "model.h"
#include "loader.h"

namespace Expl {
    Mesh::Mesh() {
        float vertices[] = {
                0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
                0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
                -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f   // top left
        };
        unsigned int indices[] = {
                0, 1, 3,
                1, 2, 3
        };

        VertexCount = 4;
        ElementCount = 6;

        //Generate buffers
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO); //Bind vertex array buffer

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

        Mode = GL_TRIANGLES;
    }

    Mesh LoadMesh(const char* filePath) {
        GLTFLoader loader{};
        loader.LoadFile(filePath);
        return Mesh();
    }
}