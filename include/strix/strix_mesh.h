#ifndef STRIX_MESH_H
#define STRIX_MESH_H

#include <strix/strix.h>
#include <strix/strix_gl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <string>
#include <vector>

namespace strix
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 textCoord;
    };

    struct Texture
    {
        uint32 id;
        std::string type;
    };

    class Mesh
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<uint32> indices;
        std::vector<Texture> textures;

        Mesh(std::vector<Vertex> vertices, std::vector<uint32> indices, std::vector<Texture> textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;

            setupMesh();
        }
        void Draw()
        {
            uint16 diffuseNr = 1;
            uint16 specularNr = 1;
            for (uint16 i = 0; i < textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);

                std::string number;
                std::string name = textures[i].type;
                if (name == "texture_diffuse")
                    number = std::to_string(diffuseNr++);
                else if (name == "texture_specular")
                    number = std::to_string(specularNr++);

                //Shader.setInt(("material." + name + number).c_str(), i);
                glBindTexture(GL_TEXTURE_2D, textures[i].id);
            }
            glActiveTexture(GL_TEXTURE0);

            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    private:
        uint32 VAO, VBO, EBO;
        void setupMesh()
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32), &indices[0], GL_STATIC_DRAW);

            // Vertex Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
            // Vertex Normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));
            // Vertex Texture Coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, textCoord));

            glBindVertexArray(0);
        }
    };
}

#endif // STRIX_MESH_H