//
// Created by MoonMoon on 2022-01-30.
//
#include "glad/gl.h"
#include "geometry.h"

#ifndef EXPLORATION_BUILTIN_GEOMETRY_H
#define EXPLORATION_BUILTIN_GEOMETRY_H

namespace Expl {
    const MeshResource cubeMeshResource{
         {
                    0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
                    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
                    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
                    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f   // top left
            },
            {
                    0, 1, 3,
                    1, 2, 3
            }
    };
}

#endif //EXPLORATION_BUILTIN_GEOMETRY_H
