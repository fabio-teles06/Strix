#include <strix/strix.h>
#include <strix/strix_renderer.h>
#include <strix/strix_logger.h>

#define STRIX_GL_DEFINE_EXTERN
#include <strix/strix_gl.h>
#undef STRIX_GL_DEFINE_EXTERN

namespace strix
{
    ShaderProgram Renderer::defaultShader;

    void Renderer::initialize()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    }

    //
    //Mesh
    //
    bool Renderer::createMesh(Mesh *outMesh, const float *vertices, int vertexCount, const unsigned int *indices, int indexCount)
    {
        outMesh->numVertices = vertexCount;
        outMesh->numIndices = indexCount;

        glGenVertexArrays(1, &outMesh->vao);
        glGenBuffers(1, &outMesh->vboPosition);
        glGenBuffers(1, &outMesh->ibo);

        glBindVertexArray(outMesh->vao);

        glBindBuffer(GL_ARRAY_BUFFER, outMesh->vboPosition);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float) * 3, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(Mesh::Attribute::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
        glEnableVertexAttribArray(Mesh::Attribute::POSITION);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, outMesh->ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

        glBindVertexArray(0);

        return true;
    }
    void Renderer::destroyMesh(Mesh *mesh)
    {
        glDeleteBuffers(1, &mesh->vboPosition);
        glDeleteBuffers(1, &mesh->ibo);
        glDeleteVertexArrays(1, &mesh->vao);
    }
    void Renderer::drawMesh(const Mesh &mesh, const ShaderProgram &shader)
    {
        glUseProgram(shader.program);
        glBindVertexArray(mesh.vao);
        glDrawElements(GL_TRIANGLES, mesh.numIndices, GL_UNSIGNED_INT, 0);
    }
    //
    // Shaders
    //
    bool Renderer::createShaderProgram(ShaderProgram *outShader, const char *vsSource, const char *fsSource)
    {
        outShader->valid = false;
        outShader->program = 0;

        GLint status;
        const int errorLogSize = 1024;
        GLsizei errorBufferLen = 0;
        char errorBuffer[errorLogSize];

        // vertex shader
        GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vsSource, 0);
        glCompileShader(vShader);
        glGetShaderiv(vShader, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            glGetShaderInfoLog(vShader, errorLogSize, &errorBufferLen, errorBuffer);
            Logger::Error("Compiling VERTEX SHADER: %s\n", errorBuffer);
            glDeleteShader(vShader);
            return false;
        }

        // fragment shader
        GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fsSource, 0);
        glCompileShader(fShader);
        glGetShaderiv(fShader, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            glGetShaderInfoLog(fShader, errorLogSize, &errorBufferLen, errorBuffer);
            Logger::Error("Compiling FRAGMENT SHADER: %s\n", errorBuffer);
            glDeleteShader(vShader);
            glDeleteShader(fShader);
            return false;
        }

        // shader program
        GLuint program = glCreateProgram();
        glAttachShader(program, vShader);
        glAttachShader(program, fShader);

        glLinkProgram(program);
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        if (!status)
        {
            glGetProgramInfoLog(program, errorLogSize, &errorBufferLen, errorBuffer);
            Logger::Error("linking SHADER: %s\n", errorBuffer);
            glDeleteShader(vShader);
            glDeleteShader(fShader);
            glDeleteProgram(program);
            return false;
        }

        // find uniforms
        outShader->numParameters = 0;
        int uniformCount = 0;
        glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &uniformCount);
        if (uniformCount > STRIX_MAX_SHADER_PARAMETERS)
        {
            Logger::Error("shader declares too many (%d) parameters. Maximum supported by material files is %d",
                          uniformCount, STRIX_MAX_SHADER_PARAMETERS);
        }

        for (int i = 0; i < uniformCount && i < STRIX_MAX_SHADER_PARAMETERS; i++)
        {
            GLsizei length;
            int size;
            GLenum type;

            ShaderParameter &parameter = outShader->parameter[outShader->numParameters];

            glGetActiveUniform(program, (GLuint)i, STRIX_MAX_SHADER_PARAMETER_NAME_LEN, &length, &size, &type, (GLchar *)&parameter.name);
            switch (type)
            {
            case GL_SAMPLER_2D:
                parameter.type = ShaderParameter::SAMPLER_2D;
                break;
            case GL_FLOAT:
                parameter.type = ShaderParameter::FLOAT;
                break;
            case GL_FLOAT_VEC2:
                parameter.type = ShaderParameter::VEC2;
                break;
            case GL_FLOAT_VEC3:
                parameter.type = ShaderParameter::VEC3;
                break;
            case GL_FLOAT_VEC4:
                parameter.type = ShaderParameter::VEC4;
                break;
            case GL_INT:
                parameter.type = ShaderParameter::INT;
                break;
            case GL_UNSIGNED_INT:
                parameter.type = ShaderParameter::UNSIGNED_INT;
                break;
            case GL_FLOAT_MAT4:
                parameter.type = ShaderParameter::MAT4;
                break;
            default:
                // TODO(marcio): We just ignore unsupported types for now. Is there a better approach ?
                continue;
                break;
            }

            parameter.glUniformLocation = glGetUniformLocation(program, parameter.name);
            outShader->numParameters++;
        }

        glDeleteShader(vShader);
        glDeleteShader(fShader);

        outShader->program = program;
        outShader->valid = true;
        return true;
    }
    ShaderProgram Renderer::getDefaultShaderProgram()
    {
        if (defaultShader.valid)
        {
            return defaultShader;
        }

        const char *vsSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            
            void main()
            {
                gl_Position = vec4(aPos, 1.0);
            }
        )";

        const char *fsSource = R"(
            #version 330 core
            out vec4 FragColor;

            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";

        bool success = createShaderProgram(&defaultShader, vsSource, fsSource);
        ASSERT(success, "Failed to create default shader program");
        return defaultShader;
    }
    void Renderer::destroyShaderProgram(ShaderProgram *shader)
    {
        glDeleteProgram(shader->program);
        shader->program = 0;
        shader->valid = false;
    }
}