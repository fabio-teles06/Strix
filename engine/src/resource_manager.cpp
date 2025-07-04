#include <strix/strix.h>
#include <strix/logger.h>
#include <strix/platform.h>
#include <strix/resource_manager.h>

namespace strix
{
    ResourceManager::ResourceManager() : initialized(false), m_meshes(16 * sizeof(Mesh)) {}
    ResourceManager &ResourceManager::get()
    {
        static ResourceManager instance;
        return instance;
    }

    void ResourceManager::initialize()
    {
        initialized = true;

        // Create default things
        // Default Texture
        // Default Shaders
        // Default Materials
    }

    ResourceManager::~ResourceManager()
    {
        int numObjects;
        const Mesh *allMeshes = getMeshes(&numObjects);
        Logger::Info("ResourceManager: Releasing Mesh x%d ", numObjects);
        for (int i = 0; i < numObjects; i++)
        {
            const Mesh *mesh = &allMeshes[i];
            // Renderer::destroyMesh((Mesh *)mesh);
        }

        m_meshes.reset();

        Logger::Info("ResourceManager destroyed, cleaned up all resources.");
    }

    //
    // Mesh Resources
    //

    Mesh *ResourceManager::getMesh(Handle<Mesh> handle) const
    {
        return m_meshes.lookup(handle);
    }

    Mesh *ResourceManager::getMeshes(int *numMeshes) const
    {
        if (numMeshes)
            *numMeshes = m_meshes.count();
        return (Mesh *)m_meshes.getArray();
    }

    Handle<Mesh> ResourceManager::createMesh(bool dynamic, const MeshData &data)
    {
        return createMesh(dynamic, Primitive::TRIANGLE,
                          data.positions, data.numPositions,
                          data.indices, data.numIndices,
                          data.colors, data.uv0, data.uv1, data.normals);
    }

    Handle<Mesh> ResourceManager::createMesh(bool dynamic, Primitive primitive,
                                             const Vector3 *vertices, int numVertices,
                                             const unsigned int *indices, int numIndices,
                                             const Color *color,
                                             const Vector2 *uv0,
                                             const Vector2 *uv1,
                                             const Vector3 *normals)
    {
        Handle<Mesh> handle = m_meshes.reserve();
        Mesh *mesh = m_meshes.lookup(handle);
        // Renderer::createMesh(mesh, dynamic, primitive, vertices, numVertices, indices, numIndices, color, uv0, uv1, normals);
        return handle;
    }

    void ResourceManager::updateMesh(Handle<Mesh> handle, MeshData *meshData)
    {
        Mesh *mesh = m_meshes.lookup(handle);
        // Renderer::updateMesh(mesh, meshData);
    }

    void ResourceManager::destroyMesh(Handle<Mesh> handle)
    {
        Mesh *mesh = m_meshes.lookup(handle);
        if (!mesh)
        {
            Logger::Warning((const char *)"Attempting to destroy a 'Mesh' resource from an invalid handle.");
        }
        else
        {
            // Renderer::destroyMesh(mesh);
            m_meshes.remove(handle);
        }
    }

}