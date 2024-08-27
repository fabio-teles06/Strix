#ifndef STRIX_RENDERER_H
#define STRIX_RENDERER_H

#include <strix/strix.h>
#include <strix/strix_renderer_types.h>

namespace strix
{

    class STRIX_API StrixRenderer final
    {
    public:
        static void clear();
        static Mesh *createMesh(
            bool dynamic, float *vertices, int numVertices,
            unsigned int *indices, int numIndices,
            float *normals, float *texcoords);
        static void drawMesh(Mesh *mesh);
    };

}

#endif