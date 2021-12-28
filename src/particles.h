//
// Created by MoonMoon on 2021-12-26.
//
#include "raymath.h"


#ifndef EXPLORATION_PARTICLES_H
#define EXPLORATION_PARTICLES_H

#define MAX_PARTICLES 512

typedef struct Particle {
    Vector3 position;
    Vector3 velocity;
} Particle;

void UpdateParticles(Particle *particles, int numParticles, float deltaTime);

void SolveForces(Particle *particles, int numParticles, float deltaTime);

void Integrate(Particle *particles, int numParticles, float deltaTime);

void CheckCollisions(Particle *particles, int numParticles, float deltaTime);

#endif //EXPLORATION_PARTICLES_H
