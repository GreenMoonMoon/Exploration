//
// Created by MoonMoon on 2021-12-27.
//
#include <malloc.h>

#include "particles.h"

void UpdateParticles(Particle *particles, int numParticles, float deltaTime) {
    SolveForces(particles, numParticles, deltaTime);
    Integrate(particles, numParticles, deltaTime);
    CheckCollisions(particles, numParticles, deltaTime);
//    SolveConstraints();
}

void SolveForces(Particle *particles, int numParticles, float deltaTime) {

}

void Integrate(Particle *particles, int numParticles, float deltaTime) {
    for (int i = 0; i < numParticles; i++) {
        particles[i].velocity = Vector3Add(particles[i].velocity,
                                           Vector3Scale((Vector3) {0.0f, -9.8f, 0.0f}, deltaTime));
//        particles[i].position = Vector3Add(particles[i].position, Vector3Scale(particles[i].velocity, deltaTime));
        particles[i].position = Vector3Add(particles[i].position, particles[i].velocity);
    }
}

void CheckCollisions(Particle *particles, int numParticles, float deltaTime) {
    for (int i = 0; i < numParticles; i++) {
        if(particles[i].position.y < 0.0f) {
            particles[i].position.y = 0.0f;
            particles[i].velocity = Vector3Scale(Vector3Negate(particles[i].velocity), 0.5);
        }
    }
}
