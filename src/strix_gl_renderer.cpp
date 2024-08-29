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

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Mesh *Renderer::createMesh(bool dynamic, float *vertices, int numVertices, unsigned int *indices, int numIndices,
                               float *normals, float *texcoords)
    {
        Mesh *mesh = new Mesh();
        mesh->dynamic = dynamic;

        // VAO
        glGenVertexArrays(1, &mesh->vao);
        glBindVertexArray(mesh->vao);

        if (numVertices)
        {
            mesh->numVertices = numVertices;
            mesh->vertexArraySize = numVertices * 3 * sizeof(float);

            glGenBuffers(1, &mesh->vboPosition);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vboPosition);
            glBufferData(GL_ARRAY_BUFFER, mesh->vertexArraySize, vertices, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
            glVertexAttribPointer(Mesh::Attribute::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glEnableVertexAttribArray(Mesh::Attribute::POSITION);
        }

        mesh->ibo = 0;
        if (numIndices)
        {
            mesh->numIndices = numIndices;
            mesh->indexArraySize = numIndices * sizeof(unsigned int);

            glGenBuffers(1, &mesh->ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indexArraySize, indices, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        if (normals)
        {
            glGenBuffers(1, &mesh->vboNormal);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vboNormal);
            glBufferData(GL_ARRAY_BUFFER, mesh->vertexArraySize, normals, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
            glVertexAttribPointer(Mesh::Attribute::NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glEnableVertexAttribArray(Mesh::Attribute::NORMAL);
        }

        if (texcoords)
        {
            glGenBuffers(1, &mesh->vboTexcoord);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vboTexcoord);
            glBufferData(GL_ARRAY_BUFFER, mesh->vertexArraySize, texcoords, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
            glVertexAttribPointer(Mesh::Attribute::TEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glEnableVertexAttribArray(Mesh::Attribute::TEXCOORD);
        }

        glBindVertexArray(0);
        return mesh;
    }

    void Renderer::drawMesh(Mesh *mesh)
    {
        glUseProgram(defaultShader.program);
        glBindVertexArray(mesh->vao);

        glEnableVertexArrayAttrib(mesh->vao, Mesh::Attribute::POSITION);
        glEnableVertexArrayAttrib(mesh->vao, Mesh::Attribute::NORMAL);
        glEnableVertexArrayAttrib(mesh->vao, Mesh::Attribute::TEXCOORD);
        glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, 0);
        glDisableVertexArrayAttrib(mesh->vao, Mesh::Attribute::POSITION);
        glDisableVertexArrayAttrib(mesh->vao, Mesh::Attribute::NORMAL);
        glDisableVertexArrayAttrib(mesh->vao, Mesh::Attribute::TEXCOORD);
    }

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
            layout (location = 1) in vec3 aNormal;
            layout (location = 2) in vec2 aTexcoord;

            out vec3 Normal;
            out vec2 Texcoord;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            void main()
            {
                // gl_Position = projection * view * model * vec4(aPos, 1.0);
                gl_Position = vec4(aPos, 1.0);
                Normal = aNormal;
                Texcoord = aTexcoord;
            }
        )";

        const char *fsSource = R"(
            #version 330 core
            out vec4 FragColor;

            in vec3 Normal;
            in vec2 Texcoord;

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