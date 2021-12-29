//
// Created by MoonMoon on 2021-12-27.
//

#include "particles.h"

void IntegrateVelocity(Particle *particle, float deltaTime) {
    particle->velocity = Vector3Add(particle->velocity, Vector3Scale(particle->acceleration, deltaTime));
    particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, deltaTime));
    particle->velocity = Vector3Scale(particle->velocity, particle->damping);
}

void IntegrateForce(Particle *particle, Vector3 force) {
    particle->acceleration = Vector3Scale(force, particle->inverseMass);
}

void SetMass(Particle *particle, float mass) {
    particle->inverseMass = 1 / mass;
}

Vector3 GetForceGravity(Particle particle, Vector3 gravity) {
    Vector3 result = Vector3Scale(gravity, (1.0f / particle.inverseMass));
    return result;
}
