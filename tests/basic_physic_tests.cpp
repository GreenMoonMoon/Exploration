//
// Created by MoonMoon on 2021-12-26.
//
#include <malloc.h>

#include "gtest/gtest.h"

extern "C" {
#include "../src/physic/particles.h"
}

TEST(Particles, IntegrationVelocity) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };

    IntegrateVelocity(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 1.0f, 0.001f);
    p.position = {0.0f, 0.0f, 0.0f};

    IntegrateVelocity(&p, 0.1f);
    EXPECT_NEAR(p.position.x, 0.1f, 0.001f);
    p.position = {0.0f, 0.0f, 0.0f};

    p.velocity.x = 0.1f;
    IntegrateVelocity(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 0.1f, 0.001f);
}

TEST(Particles, Damping) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            0.5f,
            0.5f
    };

    IntegrateVelocity(&p, 1.0f);
    EXPECT_NEAR(p.velocity.x, 0.5f, 0.001f);
}

TEST(Particles, Acceleration) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };

    p.acceleration.x = 1.0f;
    IntegrateVelocity(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 1.0f, 0.001f);

    p.acceleration.x = 2.0f;
    IntegrateVelocity(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 4.0f, 0.001f);

    p.acceleration.x = -4.0f;
    IntegrateVelocity(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 3.0f, 0.001f);
}

//Infinite mass is noted as inverseMass of 0. This should prevent the particles from moving under any forces.
TEST(Particles, InfiniteMass) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            0.0f,
            1.0f
    };

    IntegrateForce(&p, {10.0f, 0.0f, 0.0f});
    IntegrateVelocity(&p, 1.0f);
    EXPECT_EQ(p.position.x, 0.0f);
}

TEST(Particles, Force) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };

    IntegrateForce(&p, {10.0f, 0.0f, 0.0f});
    IntegrateVelocity(&p, 1.0f);
    EXPECT_EQ(p.position.x, 10.0f);
}