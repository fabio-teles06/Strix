#ifndef STRIX_VECTOR2_H
#define STRIX_VECTOR2_H

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
        Vector2 &mul(float f);
        Vector2 &div(float f);

        Vector2 &sum(float x, float y);
        Vector2 &sub(float x, float y);
        Vector2 &mul(float x, float y);
        Vector2 &div(float x, float y);

        Vector2 &sum(Vector2 &other);
        Vector2 &sub(Vector2 &other);
        Vector2 &mul(Vector2 &other);
        Vector2 &div(Vector2 &other);

        float length();
        float lengthSquared();
        Vector2 &normalize();
        Vector2 &abs();

        float dot(Vector2 &other);
        float cross(Vector2 &other);
        void set(float x, float y);
    };
}

#endif // STRIX_VECTOR2_H