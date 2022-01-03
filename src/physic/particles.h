//
// Created by MoonMoon on 2021-12-26.
//

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

    void AddForce(Vector3 force);
};

class ForceGenerator {
public:
    virtual void UpdateForce(Particle &particle, float deltaTime) = 0;
};

#endif //EXPLORATION_PARTICLES_H
