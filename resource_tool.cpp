//
// Created by MoonMoon on 2022-01-30.
//

#include <fstream>
#include <iostream>
#include <string>

#include "src/resource.h"
#include "src/builtin_geometry.h"

using namespace Expl;

enum class ResourceInput{
    Builtin,
    File
};

void save(ResourceInput inType, const char* resourceName, const char* outFilePath);

int main(int argc, char* argv[]) {
    //Tool Mode
    int mode = std::string("-save").compare(argv[1]);
    std::cout << "mode: " << mode << '\n';

    //Input
    ResourceInput inType = ResourceInput(std::string("-builtin").compare(argv[2]));
    const char* resourceName = argv[3];
    std::cout << "type: " << int(inType) << "\tname: " << resourceName << '\n';

    //Output
    //Ignore the output command for now, assume file path.
    const char* outFilePath = argv[5];
    std::cout << "output file : " << outFilePath << '\n';

    if(mode == 0){
        save(inType, resourceName, outFilePath);
    } else {
//        load();
    }
}

void save(ResourceInput inType, const char* resourceName, const char* outFilePath){
    if(inType == ResourceInput::Builtin){
        MeshResource res = cubeMeshResource;
        res.path = outFilePath;
        res.Serialize();
    }
}