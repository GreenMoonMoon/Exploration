//
// Created by MoonMoon on 2022-01-17.
//

#include "gtest/gtest.h"
#include "../src/math/expl_math.h"


using namespace Exploration;

TEST(Vector3, TestLengthZero) {
    auto v = Vector3(0, 0, 0);
    EXPECT_FLOAT_EQ(v.Length(), 0.0f);
}

TEST(Vector3, TestNormalizedZeroVector) {
    auto v = Vector3(0, 0, 0);
    v = v.Normalized();
    EXPECT_EQ(v, Vector3(0, 0, 0));
}