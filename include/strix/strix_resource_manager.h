#ifndef STRIX_RESOURCE_MANAGER_H
#define STRIX_RESOURCE_MANAGER_H

#include <strix/strix.h>
#include <strix/strix_handle.h>
#include <strix/strix_renderer_types.h>

namespace strix
{
    struct STRIX_API ResourceManager final
    {
    private:
        bool initialized;
        strix::HandleList<strix::Mesh> meshList;
        strix::HandleList<strix::ShaderProgram> shaderList;
        ShaderProgram *defaultShader;

    public:
        static ResourceManager &get();
        ~ResourceManager();
        void initialize();

        // Disallow copies
        ResourceManager(const ResourceManager &other) = delete;
        ResourceManager(const ResourceManager &&other) = delete;
        void operator=(const ResourceManager &other) = delete;
        void operator=(const ResourceManager &&other) = delete;

        // Shader Resources

        Handle<ShaderProgram> loadShader(const char *filePath);
        Handle<ShaderProgram> createShaderFromSource(const char *vertexSource, const char *fragmentSource, const char *geometrySource = nullptr);
        Handle<ShaderProgram> getDefaultShader() const;

        ShaderProgram &getShader(Handle<ShaderProgram> handle) const;
        ShaderProgram *getShaders(int *count) const;

        void destroyShader(Handle<ShaderProgram> handle);
        void destroyShader(ShaderProgram *shader);

        // Mesh Resources
        // Handle<Mesh> createMesh(bool dynamic, MeshData& meshData);
        Handle<Mesh> createMesh(bool dynamic, Primitive primitive,
                                const float *vertices, int numVertices,
                                const unsigned int *indices, int numIndices,
                                const float *colors = nullptr,
                                const float *uv0 = nullptr,
                                const float *uv1 = nullptr,
                                const float *normals = nullptr);

        // void updateMesh(Handle<Mesh> handle, MeshData *meshData);
        void destroyMesh(Handle<Mesh> handle);

        Mesh *getMesh(Handle<Mesh> handle) const;
        Mesh *getMeshes(int *count) const;
    };
}

#endif // STRIX_RESOURCE_MANAGER_H