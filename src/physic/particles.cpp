//
// Created by MoonMoon on 2021-12-27.
//

#include <cmath>

#include "particles.h"

namespace Exploration {

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

        forces = Vector3();
    }

    void Particle::SetMass(float mass) {
        inverseMass = 1.0f / mass;
    }

    float Particle::GetMass() const {
        return 1.0f / inverseMass;
    }

    void Particle::AddForce(Vector3 force) {
        forces = forces + force;
    }

    void UpdateParticles(std::vector<Particle> &particles, float frameTime) {
        for (Particle &p: particles) {
            p.Integrate(frameTime);
        }
    }

    ParticleGravity::ParticleGravity(Vector3 gravity) : gravity(gravity) {}

    void ParticleGravity::UpdateForce(Particle &particle, float deltaTime) {
        if (particle.inverseMass == 0) return;
        particle.AddForce(gravity * particle.GetMass());
    }

    ParticleDrag::ParticleDrag(float k1, float k2) : k1(k1), k2(k2) {}

    void ParticleDrag::UpdateForce(Particle &particle, float deltaTime) {
        Vector3 force = -(particle.velocity).Normalized();
        float dragCoefficient = particle.velocity.Length();
        force *= k1 * dragCoefficient + k2 * dragCoefficient * dragCoefficient;
        particle.AddForce(force);
    }
}