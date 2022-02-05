//
// Created by MoonMoon on 2022-01-17.
//
#include "src/render/render.h"
#include "src/geometry.h"

using Expl::Shader;
using Expl::MeshResource;
using Expl::Mesh;
using Expl::Renderer;

int main() {
    Renderer renderer{};

    auto shader = Shader(
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert",
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag"
    );

    auto res = MeshResource::Quad();
    auto mesh = Renderer::LoadMeshResource(res);


    while (!renderer.ShouldClose()) {
        renderer.ProcessInput();

        renderer.BeginDraw();

        Renderer::DrawMesh(mesh, shader);
        Expl::glCheckError();

        renderer.EndDraw();
    }

    return 0;
}
