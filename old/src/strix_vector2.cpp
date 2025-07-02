#include <strix/strix_vector2.h>
#include <math.h>

namespace strix
{

    inline Vector2::Vector2(float xy) : x(xy), y(xy) {}
    inline Vector2::Vector2(float x, float y) : x(x), y(y) {}

    Vector2::Vector2() {}

    void Vector2::set(float x, float y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2 &Vector2::sum(float f)
    {
        x += f;
        y += f;
        return *this;
    }

    Vector2 &Vector2::sub(float f)
    {
        x -= f;
        y -= f;
        return *this;
    }

    Vector2 &Vector2::mul(float f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    Vector2 &Vector2::div(float f)
    {
        x /= f;
        y /= f;
        return *this;
    }

    Vector2 &Vector2::sum(float x, float y)
    {
        this->x += x;
        this->y += y;
        return *this;
    }

    Vector2 &Vector2::sub(float x, float y)
    {
        this->x -= x;
        this->y -= y;
        return *this;
    }

    Vector2 &Vector2::mul(float x, float y)
    {
        this->x *= x;
        this->y *= y;
        return *this;
    }

    Vector2 &Vector2::div(float x, float y)
    {
        this->x /= x;
        this->y /= y;
        return *this;
    }

    Vector2 &Vector2::sum(Vector2 &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2 &Vector2::sub(Vector2 &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2 &Vector2::mul(Vector2 &other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2 &Vector2::div(Vector2 &other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    float Vector2::length()
    {
        return sqrt(x * x + y * y);
    }

    float Vector2::lengthSquared()
    {
        return x * x + y * y;
    }

    Vector2 &Vector2::normalize()
    {
        float l = length();
        x /= l;
        y /= l;
        return *this;
    }

    Vector2 &Vector2::abs()
    {
        x = fabs(x);
        y = fabs(y);
        return *this;
    }

    float Vector2::dot(Vector2 &other)
    {
        return x * other.x + y * other.y;
    }

    float Vector2::cross(Vector2 &other)
    {
        return (float)(x * other.y - y * other.x);
    }
}