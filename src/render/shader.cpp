//
// Created by MoonMoon on 2022-01-19.
//
#include <fstream>
#include <string>
#include <iostream>

#include "glad/gl.h"

#include "shader.h"

namespace Expl {
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

    void checkShader(unsigned int shader) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Shader compilation error:\n" << infoLog << '\n';
        }
    }

    void checkProgram(unsigned int program) {
        int success;
        char infoLog[512];
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cout << "Linking program error:\n" << infoLog << '\n';
        }
    }
}