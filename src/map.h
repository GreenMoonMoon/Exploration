//
// Created by MoonMoon on 2021-12-17.
//
#include "raymath.h"

#ifndef EXPLORATION_CHUNCK_H
#define EXPLORATION_CHUNCK_H

#define FLAT 0
#define RAMP 1
#define RAMP_LARGE 2
#define RAMP_LARGE_DETAILED 3
#define ROAD_CORNER 4
#define ROAD_CROSS 5
#define ROAD_SPLIT 6
#define ROAD_STRAIGHT 7
#define SIDE 8
#define SIDE_CLIFF 9
#define SIDE_CORNER 10
#define SIDE_CORNER_INNER 11
#define SIDE_END 12

typedef struct Vector2i {
    int x;
    int y;
} Vector2i;

typedef struct Chunk {
    char tiles[64];
    Vector3 chunkCoord;
} Chunk;

typedef struct Map {

} Map;

void LoadMap();

void UnloadMap();

void LoadChunk(Chunk *chunk);

void DrawChunks(Model terrainModel, Material terrainMaterial);

#endif //EXPLORATION_CHUNCK_H
