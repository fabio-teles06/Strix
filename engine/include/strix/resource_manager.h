#pragma once

#include <strix/strix.h>
#include <strix/resource/handle_list.h>
#include <strix/renderer/types.h>

namespace strix
{
    struct Mesh;

    class STRIX_API ResourceManager
    {
    private:
        bool initialized = false;
        HandleList<Mesh> m_meshes;

        ResourceManager();

    public:
        static ResourceManager &get();
        ~ResourceManager();
        void initialize();

        ResourceManager(const ResourceManager &) = delete;
        ResourceManager &operator=(const ResourceManager &) = delete;
        ResourceManager(ResourceManager &&) = default;
        ResourceManager &operator=(ResourceManager &&) = default;

        Handle<Mesh> createMesh(Mesh *mesh, MeshData &&data);

        //
        // Mesh Resources
        //

        Handle<Mesh> createMesh(bool dynamic, const MeshData &meshData);

        Handle<Mesh> createMesh(bool dynamic, Primitive primitive,
                                const Vector3 *vertices, int numVertices,
                                const unsigned int *indices, int numIndices,
                                const Color *color,
                                const Vector2 *uv0,
                                const Vector2 *uv1,
                                const Vector3 *normals);

        void updateMesh(Handle<Mesh> handle, MeshData *meshData);
        void destroyMesh(Handle<Mesh> handle);
        Mesh *getMesh(Handle<Mesh> handle) const;
        Mesh *getMeshes(int *numMeshes) const;
    };
}
