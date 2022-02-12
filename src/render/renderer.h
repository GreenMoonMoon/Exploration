//
// Created by MoonMoon on 2022-01-29.
//
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "render_element.h"

#include "../resource/mesh.h"
#include "../texture.h"

#ifndef EXPLORATION_RENDERER_H
#define EXPLORATION_RENDERER_H

namespace Expl {

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

    void setLayoutLocations(MeshResource &res);
}

#endif //EXPLORATION_RENDERER_H
