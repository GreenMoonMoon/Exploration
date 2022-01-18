//
// Created by MoonMoon on 2022-01-15.
//
#include <cmath>
#include <tuple>

#ifndef EXPLORATION_EXPL_MATH_H
#define EXPLORATION_EXPL_MATH_H

namespace Exploration {

// 2-dimension vector

    struct Vector2 {
        float x, y;
    };

// 3-dimension vector

    struct Vector3 {
        float x, y, z;

        Vector3() = default;

        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3 &v) const {
            return {x + v.x, y + v.y, z + v.z};
        }

        Vector3 operator-(const Vector3 &v) const {
            return {x - v.x, y - v.y, z - v.z};
        }

        Vector3 operator*(const float s) const {
            return {x * s, y * s, z * s};
        }

        Vector3 operator/(const float s) const {
            return {x / s, y / s, z / s};
        }

        Vector3 operator-() const {
            return {-x, -y, -z};
        }

        Vector3 &operator=(const Vector3 &v) = default;

        Vector3 &operator+=(const Vector3 &v) {
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        Vector3 &operator*=(const float s) {
            x *= s;
            y *= s;
            z *= s;
            return *this;
        }

        [[nodiscard]] float Length() const {
            return sqrtf(x * x + y * y + z * z);
        }

        [[nodiscard]] Vector3 Normalized() const {
            float length = this->Length();
            if (length ==0 ) return Vector3{};
            return *this / this->Length();
        }
    };

    inline bool operator==(const Vector3& lhs, const Vector3& rhs){
        return std::make_tuple(lhs.x, lhs.y, lhs.z) == std::make_tuple(rhs.x, rhs.y, rhs.z);
    }

// 4-dimension vector

    struct Vector4 {
        float x, y, z, w;
    };
}

#endif //EXPLORATION_EXPL_MATH_H
