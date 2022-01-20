//
// Created by MoonMoon on 2022-01-17.
//
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "src/render/render.h"

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

    //Register resize function
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //Set geometry
//    float vertices[] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f,  0.5f, 0.0f  // top
//    };

    //Shader
    unsigned int shaderProgram = LoadShader(
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert",
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag"
    );
    if(shaderProgram == -1){
        glfwTerminate();
        return -1;
    }

//    //Vertex buffer object VBO
//    unsigned int vbo;
//    glGenBuffers(1, &vbo);
//
//    unsigned int vao;
//    glGenVertexArrays(1, &vao);
//
//    glBindVertexArray(vao);
//
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
//
//    //Set the attribute in the glsl
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr); //Setup layout(location = 0)
//    glEnableVertexAttribArray(0);

    Mesh mesh {};
    mesh.program = shaderProgram;
    mesh.vertexCount = 3;

    while (!glfwWindowShouldClose(window)) {
        //input
        ProcessInput(window);

        //render
        glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh.Draw();

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