//
// Created by MoonMoon on 2021-12-26.
//
#include "raymath.h"


#ifndef EXPLORATION_PARTICLES_H
#define EXPLORATION_PARTICLES_H

typedef struct Particle {
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    float inverseMass;
    float damping;
} Particle;

typedef struct AgeParticle {
    Particle particle;
    float age;
} AgeParticle;

void Integrate(Particle *particle, float deltaTime);

void SetMass(Particle *particle, float mass);

#endif //EXPLORATION_PARTICLES_H
