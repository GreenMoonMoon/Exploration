//
// Created by MoonMoon on 2022-01-17.
//
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "src/render/render.h"
#include "src/model.h"

using namespace Expl;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void ProcessInput(GLFWwindow *window);

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Render Exploration 1", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Could not create a window!" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0) {
        std::cout << "Could not initialize glad!" << '\n';
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    Renderer renderer {};


    //Register resize function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Shader
    Expl::Shader shader = Shader(
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert",
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag"
    );

    Mesh mesh = LoadMesh("C:/Users/josue/CLionProjects/PhysicExploration/resources/models/suzanne.gltf");

    while (!glfwWindowShouldClose(window)) {
        //input
        ProcessInput(window);

        //render
        glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        renderer.DrawMesh(mesh, shader);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    //Cleanup

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

/// Process input for a given window
/// \param window
void ProcessInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}