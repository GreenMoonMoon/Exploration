#include <malloc.h>
#include <stdio.h>

#include "raylib.h"
#include "raymath.h"

#include "src/map.h"

#define RLIGHTS_IMPLEMENTATION

#include "src/rlights.h"

#include "src/utilities/debug_draw.h"

void loadScene();

void unloadScene();

void processInputs();

Vector2i selectTile(Camera3D camera);

Model terrainModel;
Material terrainMaterial;

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
    LoadMap();

    Chunk *chunk = malloc(sizeof(Chunk));
    chunk[0] = (Chunk){0};
    chunk->tiles[0] = 1;
    chunk->tileOrientations[0] = 3;

    chunk->coord = (Vector3){0.0f, 0.0f, 1.0f};


    LoadChunk(&chunk[0]);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //Update
        PollInputEvents();
        processInputs();

        Vector2i selectedTile;
        if (LeftClick) {
            selectedTile = selectTile(camera);
            printf("%d: %d\n", selectedTile.x, selectedTile.y);
        }

        UpdateCamera(&camera);

        BeginDrawing();
        {
            ClearBackground(BLACK);

            BeginMode3D(camera);
            {
                DrawGrid(64, 1.0f);
                DrawChunks(terrainModel, terrainMaterial);
                DrawCubeWires((Vector3){4.0f, 0.0f, 4.0f}, 8.0f, 0.0f, 8.0f, GREEN);
            }
            EndMode3D();
            DrawFPS(10, 10);
        }
        EndDrawing();
    }

    free(chunk);
    UnloadMap();
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

    terrainMaterial = LoadMaterialDefault();
    terrainMaterial.shader = shader;
    terrainMaterial.maps[MATERIAL_MAP_DIFFUSE].color = RED;
}

void unloadScene() {
    UnloadModel(terrainModel);
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