//
// Created by MoonMoon on 2022-01-29.
//
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "../geometry.h"
#include "../texture.h"

#ifndef EXPLORATION_RENDERER_H
#define EXPLORATION_RENDERER_H

namespace Expl {
    struct Mesh {
        Resource *resource = nullptr;
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;
        int VertexCount = 0;
        int IndexCount = 0;
        int Mode = -1;
    };

    struct Texture {
        unsigned int ID;

        void Use() const;
    };

    class Renderer {
    private:
        GLFWwindow *window;

    public:
        Renderer();

        ~Renderer();

        bool ShouldClose();

        void ProcessInput();

        void BeginDraw();

        void EndDraw();

        static Mesh LoadMeshResource(MeshResource &res);

        static Texture LoadTextureResource(TextureResource &res);

        static void DrawMesh(Mesh &mesh, Shader &shader);
    };


    void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    GLenum glCheckError_(const char *file, int line);
    #define glCheckError() glCheckError_(__FILE__, __LINE__)

    void setLayoutLocations(MeshResource &res);
}

#endif //EXPLORATION_RENDERER_H
