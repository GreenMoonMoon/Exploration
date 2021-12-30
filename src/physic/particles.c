//
// Created by MoonMoon on 2021-12-27.
//

#include "particles.h"

void Integrate(Particle *particle, float deltaTime) {
    //Update velocity first, semi-explicit euler integration
    particle->velocity = Vector3Add(particle->velocity, Vector3Scale(particle->acceleration, deltaTime));

    //P' = P + V * dt
    particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, deltaTime));

    //Adding damping
#ifndef SIMPLIFIED_DAMPING
    particle->velocity = Vector3Scale(particle->velocity, powf(particle->damping, deltaTime));
#else
    particle->velocity = Vector3Scale(particle->velocity, 0.9995);
#endif
}

void SetMass(Particle *particle, float mass) {
    particle->inverseMass = 1 / mass;
}