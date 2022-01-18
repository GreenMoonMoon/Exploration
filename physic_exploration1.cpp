//
// Created by MoonMoon on 2022-01-01.
//
#include <vector>

#include "raylib.h"

#include "src/physic/particles.h"


#define RANDF(x) (float)rand()/(float)(RAND_MAX/x)

int main() {
    InitWindow(800, 600, "Exploration1");

    Camera3D camera = {
            {0.0f, 8.0f, -8.0f},
            (Vector3){0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f},
            70.0f,
            CAMERA_PERSPECTIVE
    };
    SetCameraMode(camera, CAMERA_FREE);

    std::vector<Exploration::Particle> particles = std::vector<Exploration::Particle>(128);
    for (Exploration::Particle &p: particles) {
        p.position = (Exploration::Vector3) {RANDF(8.0f), RANDF(8.0f), RANDF(8.0f)};
    }

    auto g = Exploration::ParticleGravity((Exploration::Vector3){0.0f, -9.8f, 0.0f});
    auto d = Exploration::ParticleDrag(0.0f, 1.0f);

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        PollInputEvents();
        float frameTime = GetFrameTime();

        UpdateCamera(&camera);
        for(Exploration::Particle &p: particles){
            g.UpdateForce(p, frameTime);
            d.UpdateForce(p, frameTime);
        }
        UpdateParticles(particles, frameTime);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        for (Exploration::Particle &p: particles) {
            Exploration::Vector3 np = p.position - Exploration::Vector3{4.0f, 0.0f, 4.0f};
            DrawPoint3D((Vector3){np.x, np.y, np.z}, BLACK);
        }
        DrawGrid(8, 1.0f);
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
}