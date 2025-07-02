#include <strix/math/vector2.h>
#include <cmath>

namespace strix {
    inline Vector2::Vector2(float xy): x(xy), y(xy) {}   
    inline Vector2::Vector2(float x, float y): x(x), y(y) {}
    Vector2::Vector2() {}

    void Vector2::set(float x, float y) {
        this->x = x;
        this->y = y;
    }

    Vector2& Vector2::sum(float f) {
        x += f;
        y += f;
        return *this;
    }

    Vector2& Vector2::mul(float f) {
        x *= f;
        y *= f;
        return *this;
    }

    Vector2& Vector2::div(float f) {
        if (f != 0) {
            x /= f;
            y /= f;
        }
        return *this;
    }

    Vector2& Vector2::sub(float f) {
        x -= f;
        y -= f;
        return *this;
    }

    Vector2& Vector2::sum(Vector2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    Vector2& Vector2::mul(Vector2& v) {
        x *= v.x;
        y *= v.y;
        return *this;
    }

    Vector2& Vector2::div(Vector2& v) {
        if (v.x != 0 && v.y != 0) {
            x /= v.x;
            y /= v.y;
        }
        return *this;
    }

    Vector2& Vector2::sub(Vector2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    float Vector2::length() {
        return std::sqrt(x * x + y * y);
    }

    float Vector2::lengthSquared() {
        return x * x + y * y;
    }

    Vector2& Vector2::normalize() {
        float len = length();
        if (len > 0) {
            x /= len;
            y /= len;
        }
        return *this;
    }

    Vector2& Vector2::abs() {
        x = std::fabs(x);
        y = std::fabs(y);
        return *this;
    }

    float Vector2::dot(Vector2& v) const {
        return x * v.x + y * v.y;
    }

    float Vector2::cross(Vector2& v) const {
        return x * v.y - y * v.x;
    }

    bool Vector2::operator==(const Vector2& v) const {
        return x == v.x && y == v.y;
    }

    bool Vector2::operator!=(const Vector2& v) const {
        return !(*this == v);
    }

    Vector2 Vector2::operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 Vector2::operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 Vector2::operator*(const Vector2& v) const {
        return Vector2(x * v.x, y * v.y);
    }

    Vector2 Vector2::operator/(const Vector2& v) const {
        return Vector2((v.x != 0 ? x / v.x : 0), (v.y != 0 ? y / v.y : 0));
    }
}