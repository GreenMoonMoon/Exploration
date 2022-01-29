//
// Created by MoonMoon on 2022-01-29.
//

#include <string>
#include <iostream>

// Define these only in *one* .cc file.
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
// #define TINYGLTF_NOEXCEPTION // optional. disable exception handling.
#include "tiny_gltf.h"

using namespace tinygltf;


#ifndef EXPLORATION_LOADER_H
#define EXPLORATION_LOADER_H

namespace Expl {
    int GetFileExtension(const char *filePath) {
        std::string path = std::string(filePath);
        auto ext = path.substr(path.find_last_of('.') + 1);
        if (ext == "gltf") return 0;
        if (ext == "glb") return 1;
        return -1;
    }

    class GLTFLoader {
    public:
        void LoadFile(const char *filePath) {
            Model model;
            ParseFile(filePath, model);

        }

        void GetMesh(const char* meshName);

    private:
        void ParseFile(const char *filePath, Model &model) const {
            TinyGLTF loader;
            std::string err;
            std::string warn;

            bool ret;
            switch (GetFileExtension(filePath)) {
                case 0:
                    ret = loader.LoadASCIIFromFile(&model, &err, &warn, filePath);
                    break;
                case 1:
                    ret = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);
                    break;
                case -1:
                    std::cout << "Invalid file\n";
            }

            if (!warn.empty()) {
                printf("Warn: %s\n", warn.c_str());
            }

            if (!err.empty()) {
                printf("Err: %s\n", err.c_str());
            }

            if (!ret) {
                printf("Failed to parse glTF\n");
                return;
            }
        }
    };

}

#endif //EXPLORATION_LOADER_H

