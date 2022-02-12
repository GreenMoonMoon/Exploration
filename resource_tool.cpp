//
// Created by MoonMoon on 2022-01-30.
//
#include <filesystem>
#include <iostream>
#include <string>

#include "src/resource/mesh.h"

using namespace Expl;

enum class ResourceType {
    UNKNOWN,
    MESH
};

void load(const std::filesystem::path &path);

void save(std::ostream &outStream);

int main(int argc, char *argv[]) {
    if (argc < 4) {
        std::cerr << "Invalid number of argument\n" << "Usage: -load <in_file_path> -out|print [out_file_path]";
    }

    //Tool Mode
    int inMode = std::string("-load").compare(argv[1]); // 0: load
    if (inMode == 0) {
        auto inPath = std::filesystem::path(argv[2]);
        load(inPath);
    } else {
        std::cerr << "Tool mode: \"" << argv[1] << "\" not supported!";
        return -1;
    }

    int outMode = std::string("-out").compare(argv[3]); // 0: out / 1: print

    if (outMode == 0 and argc >= 5) {
        const char *outFilePath = argv[4];
        std::ofstream outFile;
        outFile.open(outFilePath);
        save(outFile);
    } else {
        save(std::cout);
    }
}

void load(const std::filesystem::path &path) {
    MeshLoader loader(path);
    loader.Load();
}

void save(std::ostream &outStream) {
}
