#ifndef STRIX_MESH_H
#define STRIX_MESH_H

#include <strix/strix.h>

namespace strix {

    struct STRIX_API Mesh {
        enum Attribute {
            POSITION = 0,
            NORMAL = 1,
            TEXCOORD = 2,
            INDEX
        };
        bool dynamic;

        unsigned int vao;
        unsigned int ibo;
        unsigned int vboPosition;
        unsigned int vboNormal;
        unsigned int vboTexcoord;

        size_t vertexArraySize;
        size_t indexArraySize;

        unsigned int numVertices;
        unsigned int numIndices;
    };

}

#endif