//
// Created by MoonMoon on 2022-01-01.
//
#include "raylib.h"
#include "src/math_utils.h"

#include "src/physic/particles.h"


int main() {
    InitWindow(800, 600, "Exploration1");

    Camera3D camera = {
            {0.0f, 8.0f, -8.0f},
            Vector3Zero(),
            {0.0f, 1.0f, 0.0f},
            70.0f,
            CAMERA_PERSPECTIVE
    };
    SetCameraMode(camera, CAMERA_FREE);

    while(!WindowShouldClose()) {
        PollInputEvents();

        BeginDrawing();
        ClearBackground(RAYWHITE);

            BeginMode3D(camera);
                DrawGrid(8, 1.0f);
            EndMode3D();
        EndDrawing();
    }

    CloseWindow();
}