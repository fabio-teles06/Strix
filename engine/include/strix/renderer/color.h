#pragma once

#include <strix/strix.h>

namespace strix
{
    struct STRIX_API Color
    {
        static const Color BLACK;
        static const Color BLUE;
        static const Color CYAN;
        static const Color GRAY;
        static const Color GREEN;
        static const Color LIME;
        static const Color MAGENTA;
        static const Color MAROON;
        static const Color NAVY;
        static const Color OLIVE;
        static const Color PURPLE;
        static const Color RED;
        static const Color SILVER;
        static const Color TEAL;
        static const Color NO_COLOR;
        static const Color WHITE;
        static const Color YELLOW;

        float r, g, b, a;

        Color();
        Color(int r, int g, int b, int a = 255);
        Color(float r, float g, float b, float a = 1.0f);
        Color(const Color& other);
    };
} // namespace strix
