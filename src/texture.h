//
// Created by MoonMoon on 2022-02-06.
//

#include "resource.h";

#ifndef EXPLORATION_TEXTURE_H
#define EXPLORATION_TEXTURE_H

namespace Expl {
    struct TextureResource : Resource {
        explicit TextureResource(const char* filePath);
    };
}

#endif //EXPLORATION_TEXTURE_H
