//
// Created by MoonMoon on 2022-01-02.
//

#include "raylib.h"

#include "src/math_utils.h"
#include "src/map.h"

int main() {
    InitWindow(800, 600, "Exploration 2");

    Camera camera = {{0.0f, 8.0f, -8.0f}, Vector3Zero(), {0.0f, 1.0f, 0.0f}, 70.0f, CAMERA_PERSPECTIVE};
    SetCameraMode(camera, CAMERA_FREE);

    Model terrainModel = LoadModel("C:/Users/josue/CLionProjects/Exploration/resources/models/terrain_models.glb");
    auto terrain = TileSet(terrainModel);

    terrain.material = LoadMaterialDefault();
    terrain.material.maps[MATERIAL_MAP_DIFFUSE].color = WHITE;

    TileMap map = TileMap(8, 8, terrain);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            map.chunks[j + i * 8].coordinate = {i - 4, 0, j - 3};
        }
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        PollInputEvents();
        UpdateCamera(&camera);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        map.Render();
        DrawGrid(8, 1.0f);
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    UnloadModel(terrainModel);
    CloseWindow();

    return 0;
}