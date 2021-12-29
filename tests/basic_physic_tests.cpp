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

TEST(Particles, SettingMass) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };

    SetMass(&p, 2.0f);
    EXPECT_FLOAT_EQ(p.inverseMass, 0.5f);
}

TEST(Particles, Gravity) {
    Particle p1 = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };
    Particle p2 = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            0.5f,
            1.0f
    };

    IntegrateForce(&p1, {0.0f, -9.8f, 0.0f});
    IntegrateVelocity(&p1, 1.0f);
    EXPECT_FLOAT_EQ(p1.position.y, -9.8f);

    IntegrateForce(&p2, GetForceGravity(p2, {0.0f, -9.8f, 0.0f}));
    IntegrateVelocity(&p2, 1.0f);
    EXPECT_FLOAT_EQ(p2.position.y, -9.8f);
}