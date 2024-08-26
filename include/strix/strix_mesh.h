#ifndef STRIX_MESH_H
#define STRIX_MESH_H

#include <strix/strix.h>
#include <strix/strix_handle.h>

#define STRIX_GL_DEFINE_EXTERN
#include <strix/strix_gl.h>
#undef STRIX_GL_DEFINE_EXTERN

namespace strix
{
    struct STRIX_API Mesh final
    {
        enum
        {
            MAX_BUFFER_PER_MESH = 6
        };

        enum Attribute
        {
            POSITIO = 0,
            UV0 = 1,
            UV1 = 2,
            NORMAL = 3,
            COLOR = 4,
            INDEX
        };

        bool dynamic;

        GLuint glPrimitive;
        GLuint vao;
        GLuint ibo;
        GLuint vboPosition;
        GLuint vboNormal;
        GLuint vboUV0;
        GLuint vboUV1;
        GLuint vboColor;
        size_t verticeArraySize;
        size_t indiceArraySize;
        unsigned int numIndices;
        unsigned int numVertices;
    };

    template class STRIX_API strix::HandleList<strix::Mesh>;
    template class STRIX_API strix::Handle<strix::Mesh>;
}

#endif // STRIX_MESH_H