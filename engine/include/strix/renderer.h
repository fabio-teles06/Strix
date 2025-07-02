#pragma once
#include <strix/strix.h>
#include <strix/renderer/types.h>

namespace strix
{
    class Renderer
    {
    public:
        static bool createMesh(Mesh *outMesh, bool dynamic,
                               const float *vertices, size_t vertexCount,
                               const uint32_t *indices, size_t indexCount);
        static void updateMesh(Mesh *mesh,
                               const float *vertices, size_t vertexCount,
                               const uint32_t *indices, size_t indexCount);

        static void destroyMesh(Mesh *mesh);
    };
} // namespace strix
