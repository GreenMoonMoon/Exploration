//
// Created by MoonMoon on 2021-12-17.
//
#include <malloc.h>

#include "raylib.h"
#include "raymath.h"
#include "map.h"

// Flat
Matrix *terrainFlatTransform;
int terrainFlatCount;

// Ramp
Matrix *terrainRampTransform;
int terrainRampCount;

// Ramp Large
Matrix *terrainRampLargeTransform;
int terrainRampLargeCount;

// Side
Matrix *terrainSideTransform;
int terrainSideCount;

// Side Cliff
Matrix *terrainSideCliffTransform;
int terrainSideCliffCount;

// Side Corner
Matrix *terrainSideCornerTransform;
int terrainSideCornerCount;

// Side Corner Inner
Matrix *terrainSideCornerInnerTransform;
int terrainSideCornerInnerCount;

// Side End
Matrix *terrainSideEndTransform;
int terrainSideEndCount;

void LoadMap() {
    terrainFlatTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainFlatCount = 0;

    terrainRampTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainRampCount = 0;

    terrainRampLargeTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainRampLargeCount = 0;

    terrainSideTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainSideCount = 0;

    terrainSideCliffTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainSideCliffCount = 0;

    terrainSideCornerTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainSideCornerCount = 0;

    terrainSideCornerInnerTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainSideCornerInnerCount = 0;

    terrainSideEndTransform = (Matrix *) malloc(sizeof(Matrix) * 64 * 9);
    terrainSideEndCount = 0;

}

void UnloadMap() {
    free(terrainFlatTransform);
    free(terrainRampTransform);
    free(terrainRampLargeTransform);
    free(terrainSideTransform);
    free(terrainSideCliffTransform);
    free(terrainSideCornerTransform);
    free(terrainSideCornerInnerTransform);
    free(terrainSideEndTransform);
}

void LoadChunk(Chunk *chunk) {
    Matrix tileMatrix;

    for (int i = 0; i < 64; i++) {
        switch (chunk->tileOrientations[i]) {
            case 0:
                tileMatrix = MatrixTranslate((i % 8) + chunk->coord.x, chunk->coord.y, floor(i / 8) + chunk->coord.z);
                break;
            case 1:
                tileMatrix = MatrixMultiply(
                        MatrixTranslate((i % 8) + chunk->coord.x, chunk->coord.y, floor(i / 8) - 1.0f + chunk->coord.z),
                        MatrixRotateY(DEG2RAD * 90)
                );
                break;
            case 2:
                tileMatrix = MatrixMultiply(
                        MatrixTranslate((i % 8) - 1.0f + chunk->coord.x, chunk->coord.y, floor(i / 8) - 1.0f + chunk->coord.z),
                        MatrixRotateY(DEG2RAD * 180)
                );
                break;
            case 3:
                tileMatrix = MatrixMultiply(
                        MatrixTranslate((i % 8) - 1.0f + chunk->coord.x, chunk->coord.y, floor(i / 8) + chunk->coord.z),
                        MatrixRotateY(DEG2RAD * 270)
                );
                break;
        }

        switch (chunk->tiles[i]) {
            case 0:
                terrainFlatTransform[terrainFlatCount] = tileMatrix;
                terrainFlatCount++;
                break;
            case 1:
                terrainRampTransform[terrainRampCount] = tileMatrix;
                terrainRampCount++;
                break;
            case 2:
                terrainRampLargeTransform[terrainRampLargeCount] = tileMatrix;
                terrainRampLargeCount++;
                break;
            case 8:
                terrainSideTransform[terrainSideCount] = tileMatrix;
                terrainSideCount++;
                break;
            case 9:
                terrainSideCliffTransform[terrainSideCliffCount] = tileMatrix;
                terrainSideCliffCount++;
                break;
            case 10:
                terrainSideCornerTransform[terrainSideCornerCount] = tileMatrix;
                terrainSideCornerCount++;
                break;
            case 11:
                terrainSideCornerInnerTransform[terrainSideCornerInnerCount] = tileMatrix;
                terrainSideCornerInnerCount++;
                break;
            case 12:
                terrainSideEndTransform[terrainSideEndCount] = tileMatrix;
                terrainSideEndCount++;
                break;
        }
    }
}

void DrawChunks(Model terrainModel, Material terrainMaterial) {
    //Draw flat
    DrawMeshInstanced(terrainModel.meshes[FLAT], terrainMaterial, terrainFlatTransform, terrainFlatCount);
    //Draw ramp
    DrawMeshInstanced(terrainModel.meshes[RAMP], terrainMaterial, terrainRampTransform, terrainRampCount);
    //Draw ramp large
    DrawMeshInstanced(terrainModel.meshes[RAMP_LARGE], terrainMaterial, terrainRampLargeTransform,
                      terrainRampLargeCount);
    //Draw side
    DrawMeshInstanced(terrainModel.meshes[SIDE], terrainMaterial, terrainSideTransform, terrainSideCount);
    //Draw side cliff
    DrawMeshInstanced(terrainModel.meshes[SIDE_CLIFF], terrainMaterial, terrainSideCliffTransform,
                      terrainSideCliffCount);
    //Draw side corner
    DrawMeshInstanced(terrainModel.meshes[SIDE_CORNER], terrainMaterial, terrainSideCornerTransform,
                      terrainSideCornerCount);
    //Draw side corner inner
    DrawMeshInstanced(terrainModel.meshes[SIDE_CORNER_INNER], terrainMaterial, terrainSideCornerInnerTransform,
                      terrainSideCornerInnerCount);
    //Draw side end
    DrawMeshInstanced(terrainModel.meshes[SIDE_END], terrainMaterial, terrainSideEndTransform, terrainSideEndCount);
}