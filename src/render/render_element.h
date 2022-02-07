//
// Created by MoonMoon on 2022-02-06.
//

#ifndef EXPLORATION_RENDER_ELEMENT_H
#define EXPLORATION_RENDER_ELEMENT_H

namespace Expl {
    struct Mesh {
        unsigned int VBO = 0;
        unsigned int VAO = 0;
        unsigned int EBO = 0;
        int VertexCount = 0;
        int IndexCount = 0;
        int Mode = -1;
    };

    struct Texture {
        unsigned int ID = 0;
    };
}

#endif //EXPLORATION_RENDER_ELEMENT_H
