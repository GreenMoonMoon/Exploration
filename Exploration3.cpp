//
// Created by MoonMoon on 2022-01-01.
//

#include "raylib.h"
#include "rlgl.h"
#include "src/math_utils.h"

struct Charater {
public:
    Transform transform;
    Model model;
public:
    void Draw();
};

void Charater::Draw() {
    DrawModel(model, transform.translation, 1.0f, BLACK);
}

int main() {
    // Setup window
    InitWindow(800, 600, "Exploration3");

    Camera3D camera = {
            {0.0f, 8.0f, -8.0f},
            Vector3Zero(),
            {0.0f, 1.0f, 0.0f},
            70.0f,
            CAMERA_PERSPECTIVE
    };
    SetCameraMode(camera, CAMERA_FREE);

    SetTargetFPS(60);

    // Init scene
    Charater player = {};
    player.model = LoadModel("../resources/models/character/test_char.glb");

    while (!WindowShouldClose()) {
        PollInputEvents();
        UpdateCamera(&camera);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        DrawGrid(8, 1.0f);
        player.Draw();
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}