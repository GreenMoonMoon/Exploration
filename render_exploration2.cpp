//
// Created by MoonMoon on 2022-01-17.
//
#include "src/render/expl_render.h"
#include "src/resource/mesh.h"
#include "src/texture.h"
#include "src/render/gl_debug.h"

#define GLM_FORCE_CXX17
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"

using Expl::Shader;
using Expl::MeshResource;
using Expl::Mesh;
using Expl::Renderer;
using Expl::TextureResource;
using Expl::Texture;

int main() {
    Renderer renderer{};

    glm::mat4x4 model;
    model = glm::identity<glm::mat4x4>();
    model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.9f));
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    Texture texture;
    {
        TextureResource tex{"C:/Users/josue/CLionProjects/PhysicExploration/resources/textures/color_grid.png"};
        texture = Renderer::LoadTextureResource(tex);
    }

    auto shader = Shader(
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert",
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag"
    );
    shader.SetVec2Uniform("uResolution", 800.0f,600.0f);
    shader.SetMat4Uniform("uModel", model);
    shader.BindTexture("tex1", texture);

    auto res = MeshResource::Quad();
    auto mesh = Renderer::LoadMeshResource(res);

    while (!renderer.ShouldClose()) {
        renderer.ProcessInput();

        model = glm::rotate(model, glm::radians((float)glfwGetTime()) * 0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetMat4Uniform("uModel", model);

        renderer.BeginDraw();

        Renderer::DrawMesh(mesh, shader);

        renderer.EndDraw();
//    Expl::glCheckError();
    }

    return 0;
}
