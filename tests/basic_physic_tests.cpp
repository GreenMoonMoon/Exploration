//
// Created by MoonMoon on 2021-12-26.
//
#include <malloc.h>

#include "gtest/gtest.h"

extern "C" {
#include "../src/physic/particles.h"
}

TEST(BasicParticles, IntegrateSteps) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };

    Integrate(&p, 1.0f);
    EXPECT_FLOAT_EQ(p.position.x, 1.0f);
}

TEST(BasicParticles, Damping) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            0.5f,
            0.5f
    };

    Integrate(&p, 1.0f);
    EXPECT_NEAR(p.velocity.x, 0.5f, 0.001f);
}

TEST(BasicParticles, Acceleration) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            1.0f
    };

    p.acceleration.x = 1.0f;
    Integrate(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 1.0f, 0.001f);

    p.acceleration.x = 2.0f;
    Integrate(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 4.0f, 0.001f);

    p.acceleration.x = -4.0f;
    Integrate(&p, 1.0f);
    EXPECT_NEAR(p.position.x, 3.0f, 0.001f);
}

//Infinite mass is noted as inverseMass of 0. This should prevent the particles from moving under any forces.
TEST(BasicParticles, InfiniteMass) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            0.0f,
            1.0f
    };

    Integrate(&p, 1.0f);
    EXPECT_EQ(p.position.x, 0.0f);
}

//TEST(BasicParticles, Force) {
//    Particle p = {
//            {0.0f, 0.0f, 0.0f},
//            {0.0f, 0.0f, 0.0f},
//            {0.0f, 0.0f, 0.0f},
//            1.0f,
//            1.0f
//    };
//
//    Integrate(&p, 1.0f);
//    EXPECT_EQ(p.position.x, 10.0f);
//}

TEST(BasicParticles, SettingMass) {
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

TEST(BasicParticles, Gravity) {
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

    p2.position = {0.0f, 0.0f, 0.0f};
    p2.velocity = {0.0f, 0.0f, 0.0f};
    p2.acceleration = {0.0f, -9.8f, 0.0f};
    Integrate(&p2, 1.0f);
    EXPECT_FLOAT_EQ(p2.position.y, -9.8f);
}