//
// Created by MoonMoon on 2022-02-06.
//

#include "resource.h"

#ifndef EXPLORATION_TEXTURE_H
#define EXPLORATION_TEXTURE_H

namespace Expl {
    struct TextureResource : Resource {
        int mipmap = 0;
        int width = 0;
        int height = 0;
        int numChannel = 0;
        unsigned char *data = nullptr;

        explicit TextureResource(const char *filePath);
        ~TextureResource();

        void Serialize() override;

        void Deserialize() override;
    };
}

#endif //EXPLORATION_TEXTURE_H
