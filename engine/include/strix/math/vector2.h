#pragma once
#include <strix/strix.h>

namespace strix{
    struct STRIX_API Vector2{
        float x;
        float y;

        Vector2();
        Vector2(float xy);
        Vector2(float x, float y);
        
        Vector2& sum(float f);
        Vector2& mul(float f);
        Vector2& div(float f);
        Vector2& sub(float f);

        Vector2& sum(Vector2& v);
        Vector2& mul(Vector2& v);
        Vector2& div(Vector2& v);
        Vector2& sub(Vector2& v);
        
        float length();
        float lengthSquared();
        Vector2& normalize();
        Vector2& abs();

        float dot(Vector2& v) const;
        float cross(Vector2& v) const;
        void set(float x, float y);

        bool operator==(const Vector2& v) const;
        bool operator!=(const Vector2& v) const;
        Vector2 operator+(const Vector2& v) const;
        Vector2 operator-(const Vector2& v) const;
        Vector2 operator*(const Vector2& v) const;
        Vector2 operator/(const Vector2& v) const;
        Vector2 operator+(float f) const;
        Vector2 operator-(float f) const;
        Vector2 operator*(float f) const;
        Vector2 operator/(float f) const;
    };
}