//
// Created by MoonMoon on 2021-12-29.
//
#include <malloc.h>

#include "gtest/gtest.h"

extern "C" {
#include "../src/physic/particles.h"
}

TEST(Particles, Forces) {
    Particle p = {
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 0.0f},
            1.0f,
            0.995f,
            0,
            2.0f,
            {0.0f, 0.0f, 0.0f}
    };
    AddForce(&p, {1.0f, 0.0f, 0.0f});
    AddForce(&p, {0.0f, 1.0f, 0.0f});

    Integrate(&p, 1.0f);

    EXPECT_FLOAT_EQ(p.position.x, 1.0f);
    EXPECT_FLOAT_EQ(p.position.y, 1.0f);
}