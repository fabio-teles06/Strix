#pragma once

#include <strix/strix.h>
#include <strix/resource/handle_list.h>

#define STRIX_GL_DEFINE_EXTERN
#include <strix/strix_gl.h>
#undef STRIX_GL_DEFINE_EXTERN

namespace strix
{
    struct STRIX_API Mesh final
    {
        enum
        {
            MAX_BUFFERS_PER_MESH = 2
        };
        enum Attribute
        {
            POSITION = 0,
            NORMAL = 1,
            TEXCOORD = 2,
            COLOR = 3,
            TANGENT = 4,
            BITANGENT = 5
        };
        bool dynamic = false;

        GLuint vao;
        GLuint ibo;
        GLuint vboPosition;

        size_t verticesArraySize = 0;
        size_t indicesArraySize = 0;
        unsigned int numIndices = 0;
        unsigned int numVertices = 0;
    };

    template class STRIX_API strix::HandleList<Mesh>;
    template class STRIX_API strix::Handle<Mesh>;
}