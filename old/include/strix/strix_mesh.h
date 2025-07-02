#ifndef STRIX_MESH_H
#define STRIX_MESH_H

#include <strix/strix.h>

#define STRIX_GL_DEFINE_EXTERN
#include <strix/strix_gl.h>
#undef STRIX_GL_DEFINE_EXTERN

namespace strix
{

    struct STRIX_API Mesh
    {
        enum
        {
            MAX_BUFFER_PER_MESH = 3
        };

        enum Attribute
        {
            POSITION = 0,
            NORMAL = 2,
            UV0 = 3,
            INDEX
        };

        bool dynamic;

        GLuint glPrimitive;
        GLuint vao;
        GLuint ibo;
        GLuint vboPosition;
        GLuint vboNormal;
        GLuint vboUV0;
        size_t verticesArraySize;
        size_t indicesArraySize;
        unsigned int numIndices;
        unsigned int numVertices;
    };

}

#endif