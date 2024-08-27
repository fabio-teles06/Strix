#include <strix/strix.h>
#include <strix/strix_renderer.h>

#define STRIX_GL_DEFINE_EXTERN
#include <strix/strix_gl.h>
#undef STRIX_GL_DEFINE_EXTERN

namespace strix
{

    void StrixRenderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Mesh *StrixRenderer::createMesh(bool dynamic, float *vertices, int numVertices, unsigned int *indices, int numIndices,
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

    void StrixRenderer::drawMesh(Mesh *mesh)
    {
        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, mesh->numIndices, GL_UNSIGNED_INT, 0);
    }
}