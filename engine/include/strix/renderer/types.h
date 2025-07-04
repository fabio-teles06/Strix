#pragma once
#include <strix/strix.h>

#include <strix/renderer/color.h>
#include <strix/renderer/mesh.h>
#include <strix/renderer/mesh_data.h>

namespace strix
{
    enum Primitive : char
    {
        TRIANGLE,
        TRIANGLE_STRIP,
        LINE,
        POINT
    };
}