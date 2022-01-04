//
// Created by MoonMoon on 2021-12-26.
//
#include <vector>

#include "../math_utils.h"

#ifndef EXPLORATION_PARTICLES_H
#define EXPLORATION_PARTICLES_H


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

    float GetMass();

    void AddForce(Vector3 force);
};

class ForceGenerator {
public:
    virtual void UpdateForce(Particle &particle, float deltaTime) = 0;
};

class Gravity : ForceGenerator {
public:
    Vector3 gravity;
public:
    explicit Gravity(Vector3 gravity);

    void UpdateForce(Particle &particle, float deltaTime) override;
};

class Drag : ForceGenerator {
public:
    void UpdateForce(Particle &particle, float deltaTime) override;
};

void UpdateParticles(std::vector<Particle> &particles, float frameTime);

#endif //EXPLORATION_PARTICLES_H
