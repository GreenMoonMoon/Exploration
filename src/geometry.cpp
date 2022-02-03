//
// Created by MoonMoon on 2022-01-23.
//
#include <fstream>


#include "glad/gl.h"
#include "geometry.h"

namespace Expl {

    MeshResource::MeshResource(std::initializer_list<float> vertices, std::initializer_list<unsigned int> indices)
            : vertices(vertices), indices(indices) {}

    void MeshResource::Serialize() {
        if (!path) return;
        std::ofstream out;
        out.open(path, std::ios::binary);
        if(!out.is_open()) return;
        size_t counts[2] = {vertices.size(), indices.size()};

        out.write(reinterpret_cast<char *>(counts), 2 * sizeof(size_t));
        out.write(reinterpret_cast<char *>(vertices.data()), vertices.size());
        out.write(reinterpret_cast<char *>(indices.data()), indices.size());

        out.close();
    }

    void MeshResource::Deserialize() {

    }

    void Mesh::LoadGL() {
        //Generate buffers
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO); //Bind vertex array buffer

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, res.vertices.size(), res.vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, res.indices.size(), res.indices.data(), GL_STATIC_DRAW);

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
}