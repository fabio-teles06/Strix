#ifndef STRIX_RENDERER_H
#define STRIX_RENDERER_H

#include <strix/strix.h>
#include <strix/strix_renderer_types.h>

namespace strix
{

    class STRIX_API Renderer final
    {
        static ShaderProgram defaultShader;

    public:

        static void initialize();

        // static void clear();
        //
        // Mesh
        //

        //
        // Shader
        //
        static bool createShaderProgram(ShaderProgram* outShader, const char* vsSource, const char* fsSource);
        static void destroyShaderProgram(ShaderProgram* shader);
        static ShaderProgram getDefaultShaderProgram();
    };

}

#endif