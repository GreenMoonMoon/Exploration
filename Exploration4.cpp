//
// Created by MoonMoon on 2022-01-01.
//

#include "raylib.h"
#include "rlgl.h"
#include "src/math_utils.h"

int main() {
    // Setup window
    InitWindow(800, 600, "Exploration3");

    Camera3D cam = {
            {0.0f, 8.0f, -8.0f},
            Vector3Zero(),
            {0.0f, 1.0f, 0.0f},
            70.0f,
            CAMERA_PERSPECTIVE
    };
    Camera3DNode camera = Camera3DNode(cam);

    SetTargetFPS(60);

    // Init scene

    while (!WindowShouldClose()) {
        PollInputEvents();
        camera.Update();

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera.camera);

        DrawGrid(8, 1.0f);

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
}