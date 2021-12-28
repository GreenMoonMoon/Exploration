//
// Created by MoonMoon on 2021-12-26.
//
#include <malloc.h>

#include "gtest/gtest.h"

extern "C" {
#include "../src/physic/particles.h"
}

TEST(PARTICES, IntegrationVelocity) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},
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