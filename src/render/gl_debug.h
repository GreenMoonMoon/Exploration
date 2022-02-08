//
// Created by MoonMoon on 2022-02-07.
//
#include "glad/gl.h"

#ifndef EXPLORATION_GL_DEBUG_H
#define EXPLORATION_GL_DEBUG_H

namespace Expl {
    GLenum glCheckError_(const char *file, int line);
    #define glCheckError() glCheckError_(__FILE__, __LINE__)
}

#endif //EXPLORATION_GL_DEBUG_H
