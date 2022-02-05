//
// Created by MoonMoon on 2022-01-30.
//

#include <fstream>
#include <iostream>
#include <string>

#include "src/resource.h"
#include "src/builtin_geometry.h"

using namespace Expl;

enum class ResourceInput {
    Builtin,
    File
};

void save(ResourceInput inType, const char *resourceName, const char *outFilePath);

void load(ResourceInput inType, const char *ressourceName, const char *inFilePath);

int main(int argc, char *argv[]) {
    //Tool Mode
    int mode = std::string("-save").compare(argv[1]);
    std::cout << "mode: " << mode << '\n';

    //Input
    ResourceInput inType = (argv[2] == std::string("-builtin")) ? ResourceInput::Builtin : ResourceInput::File;
    const char *resourceName = argv[3];
    std::cout << "type: " << int(inType) << "\tname: " << resourceName << '\n';

    //Output
    if (mode == 0) {
        const char *outFilePath = argv[5];
        std::cout << "output file : " << outFilePath << '\n';

        save(inType, resourceName, outFilePath);
    } else {
        const char *inFilePath = argv[5];
        std::cout << "input file : " << inFilePath << '\n';

        load(inType, resourceName, inFilePath);
    }
}

void save(ResourceInput inType, const char *resourceName, const char *outFilePath) {
    if (inType == ResourceInput::Builtin) {
        MeshResource res = cubeMeshResource;
        res.path = outFilePath;
        res.Serialize();
    }
}

void load(ResourceInput inType, const char *ressourceName, const char *inFilePath) {
    if (inType == ResourceInput::File) {
        MeshResource res{inFilePath};
        res.Deserialize();
    }
}
