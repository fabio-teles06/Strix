#pragma once

#include <strix/strix.h>
#include <strix/math/vector3.h>

namespace strix
{
    struct STRIX_API Mat4
    {
        float e[4][4];

        static Mat4 identity();
        static Mat4 scale(float amount);
        static Mat4 scale(float x, float y, float z);
        static Mat4 translate(float x, float y, float z);
        static Mat4 rotate(float x, float y, float z);
        static Mat4 perspective(float fov, float aspect, float zNear, float zFar);
        static Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);
        static Mat4 transpose(const Mat4 &m);
        static Mat4 inverse(const Mat4 &m);
        static Mat4 mul(const Mat4 &a, const Mat4 &b);
        static Vector3 mul(const Mat4 &a, const Vector3 &b);

        Mat4 &mul(const Mat4 &other);
        Mat4 transposed() const;
        Mat4 inverse() const;
    };
} // namespace strix