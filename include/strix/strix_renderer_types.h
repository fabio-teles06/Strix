#ifndef STRIX_RENDERER_TYPES_H
#define STRIX_RENDERER_TYPES_H

#include <strix/strix_mesh.h> // temporary include TODO: change to strix_renderer_types.h
#include <strix/strix_shader.h>

namespace strix
{
    enum Primitive : char
    {
        TRIANGLE,
        TRIANGLE_STRIP,
        LINE,
        POINT
    };

    #pragma pack(push, 1)
    struct VertexPCU
    {
        float position[3];
        float normal[3];
        float texCoord[2];
    };
    #pragma pack(pop)
}

#endif // STRIX_RENDERER_TYPES_H