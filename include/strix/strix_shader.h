#ifndef STRIX_SHADER_H
#define STRIX_SHADER_H

#include <strix/strix.h>

namespace strix
{
#define STRIX_MAX_SHADER_PARAMETER_NAME_LEN 64
    struct ShaderParameter
    {
        enum Type
        {
            SAMPLER_2D,
            FLOAT,
            INT,
            UNSIGNED_INT,
            VEC2,
            VEC3,
            VEC4,
            MAT4,
            INVALID
        };

        Type type;
        char name[STRIX_MAX_SHADER_PARAMETER_NAME_LEN];

        union
        {
            // OpenGL specific
            unsigned int glUniformLocation;
        };
    };

#define STRIX_MAX_SHADER_PARAMETERS 16
    struct STRIX_API ShaderProgram
    {
        bool valid;
        union
        {
            unsigned int program;
        };

        ShaderParameter parameter[STRIX_MAX_SHADER_PARAMETERS];
        int numParameters;
    };

}

#endif