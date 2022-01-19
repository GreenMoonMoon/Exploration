//
// Created by MoonMoon on 2022-01-17.
//
#include <string>
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "src/render/shader.h"

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
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };

    //Vertex buffer object VBO
    unsigned int vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

    //Shader
    std::string vertexSource;
    readFile(vertexSource, "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert");

    std::string fragmentSource;
    readFile(fragmentSource, "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag");

    if (vertexSource.empty() || fragmentSource.empty()) {
        glfwTerminate();
        return -1;
    }

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertex_c_str = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertex_c_str, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragment_c_str = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragment_c_str, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    while (!glfwWindowShouldClose(window)) {
        //input
        ProcessInput(window);

        //render
        glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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