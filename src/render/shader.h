//
// Created by MoonMoon on 2022-01-19.
//

#ifndef EXPLORATION_SHADER_H
#define EXPLORATION_SHADER_H

namespace Expl {
    unsigned int LoadShader(const char* vertexFile, const char* fragmentFile);

    void readFile(std::string &str, const char *filePath);

    bool checkShader(unsigned int shader);

    bool checkProgram(unsigned int program);
}

#endif //EXPLORATION_SHADER_H
