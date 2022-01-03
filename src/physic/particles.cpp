//
// Created by MoonMoon on 2021-12-27.
//

#include "particles.h"

Particle::Particle() : position({}), velocity({}), acceleration({}), forces({}), inverseMass(1), damping(9.995) {}

void Particle::Integrate(float deltaTime) {
    //Update velocity first, semi-explicit euler integration
    Vector3 accel = acceleration;
    accel += forces * inverseMass;
    velocity = velocity + accel * deltaTime;

    // Integrate velocity to update position
    // P' = P + V * dt
    position = position + velocity * deltaTime;

    //Adding damping
#ifndef SIMPLIFIED_DAMPING
    velocity = velocity * (powf(damping, deltaTime));
#else
    velocity = velocity * (0.9995);
#endif

    forces = Vector3Zero();
}

void Particle::SetMass(float mass) {
    inverseMass = 1 / mass;
}

void Particle::AddForce(Vector3 force) {
    forces = forces + force;
}

void UpdateParticles(std::vector<Particle> &particles, float frameTime) {
    for (Particle &p: particles) {
        p.Integrate(frameTime);
    }
}
