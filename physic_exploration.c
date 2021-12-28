//
// Created by MoonMoon on 2021-12-26.
//
#include <malloc.h>

#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include "src/particles.h"


#define RANDF(a) ((float)rand()/(float)(RAND_MAX) * a)


int main() {

    InitWindow(800, 600, "Physic Exploration");

    Camera3D camera = {
            (Vector3) {0.0f, 16.0f, -10.0f},
            Vector3Zero(),
            (Vector3) {0.0f, 1.0f, 0.0f},
            70,
            CAMERA_PERSPECTIVE
    };

    SetCameraMode(camera, CAMERA_FREE);

    Particle *particles = malloc(128 * sizeof(Particle));
    for (int i = 0; i < 128; i++) {
        particles[i].position = (Vector3) {RANDF(16.0f) - 8.0f, RANDF(16.0f) + 8.0f, RANDF(16.0f) - 8.0f};
        particles[i].velocity = Vector3Zero();
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // UPDATE
        PollInputEvents();

        UpdateCamera(&camera);
        UpdateParticles(particles, 128, 1.0f/60.0f);

        // RENDER
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        rlSetLineWidth(4.0f);

        DrawGrid(16, 1);
        for (int i = 0; i < 128; i++) {
            DrawPoint3D(particles[i].position, BLUE);
        }

        EndMode3D();

        DrawFPS(10, 10);
        EndDrawing();
    }

    free(particles);
    CloseWindow();

    return 0;
}