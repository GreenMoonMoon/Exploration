//
// Created by MoonMoon on 2022-01-19.
//
#include <fstream>

#include "render_element.h"

#ifndef EXPLORATION_MATERIAL_H
#define EXPLORATION_MATERIAL_H

namespace Expl {
    class Shader {
    private:
        //TODO: Define the MAX number of Textures per shader as a compile flag to enable custom number per project.
        unsigned int textures[16]{0}; //NOTE: storing only the texture IDs instead of the Expl::Texture object.
        int count = 0;
    public:
        unsigned int ID = 0;
        int tintUniformLocation = -1;

    public:
        Shader();

        Shader(const char *vertexPath, const char *fragmentPath);

        void SetUniformLocations();

        void SetVectorUniform(const char *name, float a, float b, float c) const;

        void SetVec2Uniform(const char *name, float a, float b) const;

        void BindTexture(const char *name, Texture texture);

        void Use() const;
    };

    unsigned int LoadShader(const char *vertexFile, const char *fragmentFile);

    void readFile(std::string &str, const char *filePath);

    bool checkShader(unsigned int shader);

    bool checkProgram(unsigned int program);
}

#endif //EXPLORATION_MATERIAL_H
