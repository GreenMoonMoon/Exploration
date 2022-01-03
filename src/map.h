//
// Created by MoonMoon on 2021-12-17.
//
#include <vector>

#include "raylib.h"
#include "math_utils.h"

#ifndef EXPLORATION_CHUNK_H
#define EXPLORATION_CHUNK_H

struct Coordinate {
    int x, y, z;
};

class TileSet {
public:
    Material material;
    Mesh *meshes;
    int tileCount;
public:
    explicit TileSet(Model model);
};

class Chunk {
public:
    int tileInstances[64] = {};
    Coordinate coordinate;
public:
    Chunk();
    void Render(TileSet &set);
};

class TileMap {
public:
    TileSet tileSet;
    std::vector<Chunk> chunks;
public:
    TileMap(int columns, int rows, TileSet set);

    void Render();
};

#endif //EXPLORATION_CHUNK_H
