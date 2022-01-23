//
// Created by MoonMoon on 2022-01-19.
//

#ifndef EXPLORATION_MATERIAL_H
#define EXPLORATION_MATERIAL_H

namespace Expl {

    class Material {
    public:
        unsigned int program;

    public:
        Material();
        Material(const char* vertexPath, const char* fragmentPath);
    };

    unsigned int LoadShader(const char* vertexFile, const char* fragmentFile);

    void readFile(std::string &str, const char *filePath);

    bool checkShader(unsigned int shader);

    bool checkProgram(unsigned int program);
}

#endif //EXPLORATION_MATERIAL_H
