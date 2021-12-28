//
// Created by MoonMoon on 2021-12-27.
//
#include <malloc.h>

#include "particles.h"

void IntegrateVelocity(Particle *particle, float deltaTime) {
    particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, deltaTime));
}
