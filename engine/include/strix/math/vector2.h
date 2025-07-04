#pragma once

#include <strix/strix.h>

namespace strix
{
    struct STRIX_API Vector2
    {
        float x;
        float y;

        Vector2();
        Vector2(float xy);
        Vector2(float x, float y);

        Vector2 &sum(float f);
        Vector2 &sub(float f);
        Vector2 &mult(float f);
        Vector2 &div(float f);

        Vector2 &sum(Vector2 &other);
        Vector2 &sub(Vector2 &other);
        Vector2 &mult(Vector2 &other);
        Vector2 &div(Vector2 &other);

        Vector2 &sum(float x, float y);
        Vector2 &sub(float x, float y);
        Vector2 &mult(float x, float y);
        Vector2 &div(float x, float y);

        float length();
        Vector2 &normalized();
        Vector2 &abs();

        float dot(Vector2 &other);
        float cross(Vector2 &other);
        void set(float x, float y);
    };
} // namespace strix
