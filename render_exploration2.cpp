//
// Created by MoonMoon on 2022-01-17.
//
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "src/render/render.h"
#include "src/geometry.h"

using namespace Expl;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void ProcessInput(GLFWwindow *window);

GLenum glCheckError_(const char *file, int line);

#define glCheckError() glCheckError_(__FILE__, __LINE__)

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

    //Shader
    Shader shader = Shader(
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.vert",
            "C:/Users/josue/CLionProjects/PhysicExploration/resources/shaders/basic.frag"
    );

    MeshResource res = MeshResource::Quad();
    Mesh mesh = Renderer::LoadMeshResource(res);


    while (!glfwWindowShouldClose(window)) {
        //input
        ProcessInput(window);

        //render
        glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Renderer::DrawMesh(mesh, shader);
        glCheckError();

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

GLenum glCheckError_(const char *file, int line) {
    GLenum errorCode;
    while (errorCode = glGetError(), errorCode != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_STACK_OVERFLOW:
                error = "STACK_OVERFLOW";
                break;
            case GL_STACK_UNDERFLOW:
                error = "STACK_UNDERFLOW";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << '\n';
    }
    return errorCode;
}
