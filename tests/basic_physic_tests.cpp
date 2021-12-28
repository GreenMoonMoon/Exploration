//
// Created by MoonMoon on 2021-12-26.
//
#include <malloc.h>

#include "gtest/gtest.h"

#include "../src/particles.h"


TEST(PARTICLES, Initialization) {
    auto *p = (Particle *) malloc(8 * sizeof(Particle));

    for (int i = 0; i < 8; i++) {
        p[i].velocity = {0.0f, 0.0f, 0.0f};
    }

    free(p);
}