//
// Created by MoonMoon on 2022-01-01.
//
#include <vector>

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

    std::vector<Particle> particles = std::vector<Particle>(128);
    for (Particle &p: particles) {
        p.position = (Vector3) {RANDF(8.0f), RANDF(8.0f), RANDF(8.0f)};
        p.acceleration = (Vector3) {0.0f, -9.8f, 0.9f};
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        PollInputEvents();
        UpdateCamera(&camera);
        UpdateParticles(particles, GetFrameTime());

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        for (Particle &p: particles) {
            DrawPoint3D(p.position - (Vector3) {4.0f, 0.0f, 4.0f}, BLACK);
        }
        DrawGrid(8, 1.0f);
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}