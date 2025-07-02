#include <strix/logger.h>
#include <strix/renderer.h>

namespace strix
{
    bool Renderer::createMesh(Mesh *outMesh, bool dynamic,
                              const float *vertices, size_t numVertices,
                              const uint32_t *indices, size_t numIndices)
    {
        if (!outMesh)
            return false;

        Mesh *mesh = outMesh;
        mesh->dynamic = dynamic;

        // VAO
        glGenVertexArrays(1, &mesh->vao);
        glBindVertexArray(mesh->vao);
        GLenum bufferHint = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;

        if (numVertices)
        {
            mesh->numVertices = numVertices;
            mesh->verticesArraySize = numVertices * sizeof(float) * 3; // Assuming 3 floats per vertex (x, y, z)

            glGenBuffers(1, &mesh->vboPosition);
            glBindBuffer(GL_ARRAY_BUFFER, mesh->vboPosition);
            glBufferData(GL_ARRAY_BUFFER, mesh->verticesArraySize, vertices, bufferHint);
            glVertexAttribPointer(Mesh::POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glEnableVertexAttribArray(Mesh::POSITION);
        }

        mesh->ibo = 0;
        if (numIndices)
        {
            mesh->numIndices = numIndices;
            mesh->indicesArraySize = numIndices * sizeof(uint32_t);

            glGenBuffers(1, &mesh->ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indicesArraySize, indices, bufferHint);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        glBindVertexArray(0); // Unbind VAO
        return true;
    }

    void Renderer::updateMesh(Mesh *mesh, const float *vertices, size_t numVertices,
                              const uint32_t *indices, size_t numIndices)
    {
        if (!mesh)
            return;

        if (!mesh->dynamic)
        {
            Logger::Warning("Mesh is not dynamic, cannot update.");
            return;
        }

        bool resizeBuffers = false;
    }

    void Renderer::destroyMesh(Mesh *mesh)
    {
        GLuint buffers[Mesh::MAX_BUFFERS_PER_MESH];
        int numBuffers = 0;

        if (mesh->ibo)
            buffers[numBuffers++] = mesh->ibo;
        if (mesh->vboPosition)
            buffers[numBuffers++] = mesh->vboPosition;

        glDeleteBuffers(numBuffers, (const GLuint *)buffers);
        glDeleteVertexArrays(1, (const GLuint *)&mesh->vao);
    }
}