//
// Created by MoonMoon on 2022-01-19.
//
#include <fstream>

#ifndef EXPLORATION_MATERIAL_H
#define EXPLORATION_MATERIAL_H

namespace Expl {

    class Shader {
    public:
        unsigned int glProgram;
        int tintUniformLocation;

    public:
        Shader();

        Shader(const char* vertexPath, const char* fragmentPath);

        void SetUniformLocations();

        void SetVectorUniform(char* name, float a, float b, float c) const;

        void Use() const;
    };

    unsigned int LoadShader(const char* vertexFile, const char* fragmentFile);

    void readFile(std::string &str, const char *filePath);

    bool checkShader(unsigned int shader);

    bool checkProgram(unsigned int program);
}

#endif //EXPLORATION_MATERIAL_H
