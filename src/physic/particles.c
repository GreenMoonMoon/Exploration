//
// Created by MoonMoon on 2021-12-27.
//
#include <malloc.h>

#include "particles.h"

void IntegrateVelocity(Particle *particle, float deltaTime) {
    particle->velocity = Vector3Add(particle->velocity, Vector3Scale(particle->acceleration, deltaTime));
    particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, deltaTime));
    particle->velocity = Vector3Scale(particle->velocity, particle->damping);
}

void IntegrateForce(Particle *particle, Vector3 force) {
    particle->acceleration = Vector3Scale(force, particle->inverseMass);
}
