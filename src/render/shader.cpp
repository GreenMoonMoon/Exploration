//
// Created by MoonMoon on 2022-01-19.
//
#include <fstream>
#include <string>
#include <iostream>

#include "glad/gl.h"

#include "shader.h"

namespace Expl {
    unsigned int LoadShader(const char* vertexFile, const char* fragmentFile) {
        std::string vertexSource;
        readFile(vertexSource, vertexFile);

        std::string fragmentSource;
        readFile(fragmentSource, fragmentFile);

        if (vertexSource.empty() || fragmentSource.empty()) {
            return -1;
        }

        unsigned int vertexShader;
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const char *vertex_c_str = vertexSource.c_str();
        glShaderSource(vertexShader, 1, &vertex_c_str, nullptr);
        glCompileShader(vertexShader);
        if(!checkShader(vertexShader)) return -1;

        unsigned int fragmentShader;
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fragment_c_str = fragmentSource.c_str();
        glShaderSource(fragmentShader, 1, &fragment_c_str, nullptr);
        glCompileShader(fragmentShader);
        if(!checkShader(fragmentShader)) return -1;

        unsigned int shaderProgram;
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        checkProgram(shaderProgram);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
    }

/// Fill a C-style string with the content of a text file
/// \param str
/// \param filePath
    void readFile(std::string &str, const char *filePath) {
        std::ifstream in(filePath);
        if (!in) {
            std::cout << "Could not open: " << filePath << '\n';
        }
        str = {std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>()};
        in.close();
    }

    bool checkShader(unsigned int shader) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Shader compilation error:\n" << infoLog << '\n';
            return false;
        }
        return true;
    }

    bool checkProgram(unsigned int program) {
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cout << "Linking program error:\n" << infoLog << '\n';
            return false;
        }
        return true;
    }
}