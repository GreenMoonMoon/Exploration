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
    for (int i = 0; i < 64; i++) {
        switch (chunk->tiles[i]) {
            case 0:
                terrainFlatTransform[terrainFlatCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainFlatCount++;
                break;
            case 1:
                terrainRampTransform[terrainRampCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainRampCount++;
                break;
            case 2:
                terrainRampLargeTransform[terrainRampLargeCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainRampLargeCount++;
                break;
            case 8:
                terrainSideTransform[terrainSideCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainSideCount++;
                break;
            case 9:
                terrainSideCliffTransform[terrainSideCliffCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainSideCliffCount++;
                break;
            case 10:
                terrainSideCornerTransform[terrainSideCornerCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainSideCornerCount++;
                break;
            case 11:
                terrainSideCornerInnerTransform[terrainSideCornerInnerCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
                terrainSideCornerInnerCount++;
                break;
            case 12:
                terrainSideEndTransform[terrainSideEndCount] = MatrixTranslate(
                        (i % 8) + chunk->chunkCoord.x,
                        chunk->chunkCoord.y,
                        floor(i / 8) + chunk->chunkCoord.z
                );
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