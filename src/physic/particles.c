//
// Created by MoonMoon on 2021-12-27.
//

#include "particles.h"

void Integrate(Particle *particle, float deltaTime) {
    //Update velocity first for semi-explicit euler integration
    particle->velocity = Vector3Add(particle->velocity, Vector3Scale(particle->acceleration, deltaTime));

    // Short form, useful for most cases
    //P' = P + V * dt
    particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, deltaTime));

      // Long from, use with large acceleration values
//    // P' = P + V * dt + 0.5 * A * dt * dt
//    particle->position = Vector3Add(
//            particle->position,
//            Vector3Add(
//                    Vector3Scale(particle->velocity, deltaTime),
//                    Vector3Scale(particle->acceleration, 0.5f * deltaTime * deltaTime)
//            )
//    );

//    particle->velocity = Vector3Add(particle->velocity, Vector3Scale(particle->acceleration, deltaTime));
//    particle->position = Vector3Add(particle->position, Vector3Scale(particle->velocity, deltaTime));
//    particle->velocity = Vector3Scale(particle->velocity, particle->damping);
}

void SetMass(Particle *particle, float mass) {
    particle->inverseMass = 1 / mass;
}