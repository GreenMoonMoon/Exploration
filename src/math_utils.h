//
// Created by MoonMoon on 2022-01-01.
//
#include "raymath.h"

#ifndef EXPLORATION_MATH_UTILS_H
#define EXPLORATION_MATH_UTILS_H

#define RANDF(a) (float)rand()/(float)(RAND_MAX/a)

//Vector3
inline Vector3 operator*(Vector3 v, float s) {
    return Vector3Scale(v, s);
}

inline Vector3 operator+(const Vector3 &v1, const Vector3 &v2 ) {
    return Vector3Add(v1, v2);
}

inline Vector3 operator-(const Vector3 &v1, const Vector3 &v2 ) {
    return Vector3Subtract(v1, v2);
}

inline Vector3 operator+=(Vector3 &v1, const Vector3 &v2) {
    return Vector3Add(v1, v2);
}

#endif //EXPLORATION_MATH_UTILS_H
