//
// Created by MoonMoon on 2022-01-29.
//
#include <iostream>

#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "../geometry.h"

#ifndef EXPLORATION_RENDERER_H
#define EXPLORATION_RENDERER_H

namespace Expl {

    bool GLFW_INITIALIZED = false;

    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    struct Mesh {
        Resource *resource = nullptr;
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;
        int VertexCount = 0;
        int IndexCount = 0;
        int Mode = -1;
    };

    class Renderer {
    private:
        GLFWwindow *window;

    public:
        Renderer() {
            if (!GLFW_INITIALIZED) GLFW_INITIALIZED = glfwInit();

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // MacOS
            glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

            window = glfwCreateWindow(800, 600, "Render Exploration 1", nullptr, nullptr);
            if (window == nullptr) {
                std::cout << "Could not create a window!" << '\n';
                glfwTerminate();
                return;
            }
            glfwMakeContextCurrent(window);

            int version = gladLoadGL(glfwGetProcAddress);
            if (version == 0) {
                std::cout << "Could not initialize glad!" << '\n';
                glfwTerminate();
                return;
            }

            glViewport(0, 0, 800, 600);

            //Register resize function
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        }

        ~Renderer() {
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        bool ShouldClose() {
            return glfwWindowShouldClose(window);
        }

        void ProcessInput() {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, GLFW_TRUE);
        }

        void BeginDraw() {
            glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

        void EndDraw() {
            glfwPollEvents();
            glfwSwapBuffers(window);
        }

        static Mesh LoadMeshResource(MeshResource &res) {
            //Generate buffers
            unsigned int vbo;
            unsigned int ebo;
            unsigned int vao;
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            glGenVertexArrays(1, &vao);

            glBindVertexArray(vao); //Bind vertex array buffer

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(res.vertices.size() * sizeof(float)),
                         res.vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(res.indices.size() * sizeof(int)),
                         res.indices.data(), GL_STATIC_DRAW);

            //Set the attribute in the glsl
            //Setup layout(location = 0)
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * (int) sizeof(float), nullptr);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            glEnableVertexAttribArray(0);
//        //Setup layout(location = 1)
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * (int) sizeof(float), (void *) (3 * sizeof(float)));
//        glEnableVertexAttribArray(1);

            //Unbind buffers
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            int mode = GL_TRIANGLES;
            return Mesh{
                    .resource = &res,
                    .VBO = vbo,
                    .VAO = vao,
                    .EBO = ebo,
                    .VertexCount = (int) res.vertices.size(),
                    .IndexCount = (int) res.indices.size(),
                    .Mode = mode
            };
        }

        static void DrawMesh(Mesh &mesh, Shader &shader) {
            shader.Use();
//            shader.SetVectorUniform("tint", 0.0f, 1.0f, 0.0f);

            glBindVertexArray(mesh.VAO);
            glDrawElements(mesh.Mode, mesh.IndexCount, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
        }
    };

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

#define glCheckError() glCheckError_(__FILE__, __LINE__)
}

#endif //EXPLORATION_RENDERER_H
