//
// Created by MoonMoon on 2022-01-19.
//

#ifndef EXPLORATION_SHADER_H
#define EXPLORATION_SHADER_H

namespace Expl {
    void readFile(std::string &str, const char *filePath);

    void checkShader(unsigned int shader);

    void checkProgram(unsigned int program);
}

#endif //EXPLORATION_SHADER_H
