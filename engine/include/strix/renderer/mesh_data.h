#pragma once

#include <strix/strix.h>

namespace strix
{
    struct Vector3;
    struct Color;
    struct Vector2;

    struct STRIX_API MeshData
    {
        const Vector3 *positions;
        const unsigned int *indices;
        const Color *colors;
        const Vector2 *uv0;
        const Vector2 *uv1;
        const Vector3 *normals;
        int numPositions;
        int numIndices;

        MeshData();
        MeshData(Vector3 *positions, int numPositions, unsigned int *indices = nullptr, int numIndices = 0);

        MeshData& setPosition(Vector3* positions);
        MeshData& setIndices(unsigned int* indices);

        MeshData(const MeshData& other);

        static const MeshData getPrimitiveCube();
    };
}