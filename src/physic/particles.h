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

void IntegrateForce(Particle *particle, Vector3 force);

void IntegrateVelocity(Particle *particle, float deltaTime);

#endif //EXPLORATION_PARTICLES_H
