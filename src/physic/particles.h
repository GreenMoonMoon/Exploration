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
    float inverseMass;
    float damping;
    float age;
    float ageLimit;
    Vector3 forces;

void Integrate(float deltaTime);

void SetMass(float mass);

void AddForce(Vector3 force);
};

#endif //EXPLORATION_PARTICLES_H
