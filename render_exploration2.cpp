//
// Created by MoonMoon on 2022-01-17.
//
#include "src/render/expl_render.h"
#include "src/geometry.h"
#include "src/texture.h"
#include "src/render/gl_debug.h"

//#define GLM_FORCE_CXX17

using Expl::Shader;
using Expl::MeshResource;
using Expl::Mesh;
using Expl::Renderer;
using Expl::TextureResource;
using Expl::Texture;

int main() {


    Renderer renderer{};

    auto shader = Shader(
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert",
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag"
    );
    shader.SetVec2Uniform("resolution", 800.0f,600.0f);

    Texture texture;
    {
        TextureResource tex{"C:/Users/josue/CLionProjects/PhysicExploration/resources/textures/color_grid.png"};
        texture = Renderer::LoadTextureResource(tex);
    }
    shader.BindTexture("tex1", texture);

    auto res = MeshResource::Quad();
    auto mesh = Renderer::LoadMeshResource(res);

    while (!renderer.ShouldClose()) {
        renderer.ProcessInput();

        renderer.BeginDraw();

        Renderer::DrawMesh(mesh, shader);

        renderer.EndDraw();
//    Expl::glCheckError();
    }

    return 0;
}
