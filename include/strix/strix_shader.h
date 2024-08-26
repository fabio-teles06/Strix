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
            VECTOR2,
            VECTOR3,
            VECTOR4,
            FLOAT,
            INT,
            UNSINGED_INT,
            MATRIX4,
            INVALID
        };

        Type type;
        char name[STRIX_MAX_SHADER_PARAMETER_NAME_LEN];

        union
        {
            unsigned int glUniformLocation;
        };
    };

#define STRIX_MAX_SHADER_PARAMETERS 16
    struct STRIX_API ShaderProgram
    {
        bool valid;
        union
        {
            unsigned int glProgramId;
        };

        ShaderParameter parameters[STRIX_MAX_SHADER_PARAMETERS];
        int parameterCount;
    };

}

#endif // STRIX_SHADER_H