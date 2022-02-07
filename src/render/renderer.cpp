//
// Created by MoonMoon on 2022-02-04.
//
#include "renderer.h"

namespace Expl {
    bool GLFW_INITIALIZED = false;

    Renderer::Renderer() {
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

    Renderer::~Renderer() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    bool Renderer::ShouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Renderer::ProcessInput() {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    void Renderer::BeginDraw() {
        glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::EndDraw() {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    Mesh Renderer::LoadMeshResource(MeshResource &res) {
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

        //Bind vertex attributes
        setLayoutLocations(res);

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

    void Renderer::DrawMesh(Mesh &mesh, Shader &shader) {
        shader.Use();
//            shader.SetVectorUniform("tint", 0.0f, 1.0f, 0.0f);

        glBindVertexArray(mesh.VAO);
        glDrawElements(mesh.Mode, mesh.IndexCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }

    Texture Renderer::LoadTextureResource(TextureResource &res) {
        unsigned int texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //TODO handle failure
        int type;
        switch (res.numChannel) {
            case(3): type = GL_RGB; break;
            case(4): type = GL_RGBA; break;
        }

        glTexImage2D(GL_TEXTURE_2D, res.mipmap, GL_RGB, res.width, res.height, 0, type, GL_UNSIGNED_BYTE, res.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        return Texture{
            texture
        };
    }

    void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
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

    void setLayoutLocations(MeshResource &res) {
        // Setup layout(location = 0): Vertex positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);

        // Setup layout(location = 1): UVs
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Setup layout(location = 2) Vertex colors
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (5 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }

    void Texture::Use() const {
        glBindTexture(GL_TEXTURE_2D, ID);
    }
}