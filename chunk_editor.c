#include <malloc.h>
#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#include "src/chunk.h"

#define RLIGHTS_IMPLEMENTATION

#include "src/rlights.h"

#include "src/utilities/debug_draw.h"

typedef struct Vector2i {
    int x;
    int y;
} Vector2i;

typedef struct Chunk {
    char tiles[64];
    Matrix tileTransforms[64];
    Vector3 chunkCoord;
} Chunk;

void loadScene();

void unloadScene();

void processInputs();

void LoadChunk(Chunk *chunk);

void DrawChunks();

Vector2i selectTile(Camera3D camera);

Model terrainModel;
Material terrainMaterial;

Matrix *terrainFlatTransform;
int terrainFlatCount;

bool LeftClick = false;
bool LeftClickReleased = true;


int main() {
    InitWindow(800, 600, "Exploration");

    Camera3D camera = {
            (Vector3) {4.0f, 8.0f, 4.0f},
            (Vector3) {0.0f, 0.0f, 4.0f},
            (Vector3) {0.0f, 1.0f, 0.0f},
            70,
            CAMERA_PERSPECTIVE
    };
    SetCameraMode(camera, CAMERA_FREE);

    loadScene();

    terrainFlatTransform = malloc(sizeof(Matrix) * 64 * 9);
    terrainFlatCount = 0;

    Chunk *chunk = malloc(sizeof(Chunk) * 9);

    for (int c = 0; c < 9; c++) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                chunk[c].tileTransforms[i * 8 + j] = MatrixTranslate(
                        (float) j + chunk[c].chunkCoord.x,
                        0.0f + chunk[c].chunkCoord.y,
                        (float) i + chunk[c].chunkCoord.z
                );
            }
        }
    }
    chunk[0].chunkCoord = (Vector3) {-8.0f, 0.0f, -8.0f};
    chunk[1].chunkCoord = (Vector3) {0.0f, 0.0f, -8.0f};
    chunk[2].chunkCoord = (Vector3) {8.0f, 0.0f, -8.0f};
    chunk[3].chunkCoord = (Vector3) {-8.0f, 0.0f, 0.0f};
    chunk[4].chunkCoord = (Vector3) {0.0f, 0.0f, 0.0f};
    chunk[5].chunkCoord = (Vector3) {8.0f, 0.0f, 0.0f};
    chunk[6].chunkCoord = (Vector3) {-8.0f, 0.0f, 8.0f};
    chunk[7].chunkCoord = (Vector3) {0.0f, 0.0f, 8.0f};
    chunk[0].chunkCoord = (Vector3) {8.0f, 0.0f, 8.0f};

    for(int i = 0; i < 9; i++){
        LoadChunk(&chunk[i]);
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //Update
        PollInputEvents();
        processInputs();

        Vector2i selectedTile;
        if (LeftClick) {
            selectedTile = selectTile(camera);
        }

        UpdateCamera(&camera);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                DrawGrid(64, 1.0f);
                DrawChunks();
                DrawCubeWires((Vector3) {4.0f, 0.1f, -4.0f}, 8.0f, 0.0f, 8.0f, GREEN);
            }
            EndMode3D();
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    free(chunk);
    free(terrainFlatTransform);
    unloadScene();
    CloseWindow();
}

void loadScene() {
    terrainModel = LoadModel("C:/Users/josue/CLionProjects/Exploration/resources/models/terrain_models.glb");

    //Set terrain material
    Shader shader = LoadShader(
            TextFormat("C:/Users/josue/CLionProjects/Exploration/resources/shaders/base_lighting_instanced.vs"),
            TextFormat("C:/Users/josue/CLionProjects/Exploration/resources/shaders/lighting.fs")
    );

    // Get some shader locations
    shader.locs[SHADER_LOC_MATRIX_MVP] = GetShaderLocation(shader, "mvp");
    shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
    shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocationAttrib(shader, "instanceTransform");

    // Ambient light level
    int ambientLoc = GetShaderLocation(shader, "ambient");
    SetShaderValue(shader, ambientLoc, (float[4]) {0.2f, 0.2f, 0.2f, 1.0f}, SHADER_UNIFORM_VEC4);

    CreateLight(LIGHT_DIRECTIONAL, (Vector3) {50.0f, 50.0f, 0.0f}, Vector3Zero(), WHITE, shader);

    // NOTE: We are assigning the instancing shader to material.shader
    // to be used on mesh drawing with DrawMeshInstanced()
    terrainMaterial = LoadMaterialDefault();
    terrainMaterial.shader = shader;
    terrainMaterial.maps[MATERIAL_MAP_DIFFUSE].color = RED;
}

void unloadScene() {
    UnloadModel(terrainModel);
}

void LoadChunk(Chunk *chunk) {
    for (int i = 0; i < 64; i++) {
        switch (chunk->tiles[i]) {
            case 0:
                terrainFlatTransform[terrainFlatCount] = MatrixMultiply(
                        chunk->tileTransforms[i],
                        MatrixTranslate(chunk->chunkCoord.x, chunk->chunkCoord.y, chunk->chunkCoord.z)
                );
                terrainFlatCount++;
                break;
        }
    }
}

void DrawChunks() {
    DrawMeshInstanced(terrainModel.meshes[0], terrainMaterial, terrainFlatTransform, terrainFlatCount);
}

void processInputs() {
    if (LeftClickReleased && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        LeftClick = true;
        LeftClickReleased = false;
    }
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) LeftClickReleased = true;
}

Vector2i selectTile(Camera3D camera) {
    Vector2i tileCoord = {-1};
    Ray ray = GetMouseRay(GetMousePosition(), camera);
    RayCollision gridHit = GetRayCollisionQuad(
            ray,
            (Vector3) {-4.0f, 0.0f, -4.0f}, (Vector3) {4.0f, 0.0f, 4.0f},
            (Vector3) {-4.0f, 0.0f, 4.0f}, (Vector3) {4.0f, 0.0f, -4.0f}
    );
    if (gridHit.hit) {
        tileCoord.x = floorf(gridHit.point.x) + 0.5f;
        tileCoord.y = floorf(gridHit.point.z) + 0.5f;
    }
    LeftClick = false;
    return tileCoord;
}