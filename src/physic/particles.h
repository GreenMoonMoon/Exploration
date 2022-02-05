//
// Created by MoonMoon on 2021-12-26.
//
#include <vector>

#include "../math/vector.h"

#ifndef EXPLORATION_PARTICLES_H
#define EXPLORATION_PARTICLES_H

namespace Exploration {

    class Particle {
    public:
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 forces;
        float inverseMass;
        float damping;

    public:
        Particle();

        void Integrate(float deltaTime);

        void SetMass(float mass);

        float GetMass() const;

        void AddForce(Vector3 force);
    };

    class ForceGenerator {
    public:
        virtual void UpdateForce(Particle &particle, float deltaTime) = 0;
    };

    class ParticleGravity : ForceGenerator {
    public:
        Vector3 gravity;
    public:
        explicit ParticleGravity(Vector3 gravity);

        void UpdateForce(Particle &particle, float deltaTime) override;
    };

    class ParticleDrag : ForceGenerator {
    public:
        float k1;
        float k2;
    public:
        ParticleDrag(float k1, float k2);

        void UpdateForce(Particle &particle, float deltaTime) override;
    };

    void UpdateParticles(std::vector<Particle> &particles, float frameTime);

}

#endif //EXPLORATION_PARTICLES_H
