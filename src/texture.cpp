//
// Created by MoonMoon on 2022-02-06.
//
#include <iostream>

#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb/stb_image.h"

namespace Expl{
    TextureResource::TextureResource(const char *filePath) {
        stbi_set_flip_vertically_on_load(true);
        data = stbi_load(filePath, &width, &height, &numChannel, 0);
        if(data == nullptr){
            std::cerr << "Could not load " << filePath << '\n';
        }
    }

    TextureResource::~TextureResource() {
        stbi_image_free(data);
    }

    void TextureResource::Serialize() {

    }

    void TextureResource::Deserialize() {

    }
}
