#pragma once

#include <strix/strix.h>
#include <strix/resource/handle_list.h>
#include <strix/renderer/types.h>

namespace strix
{
    struct Mesh;

    struct STRIX_API ResourceManager final
    {
    private:
        bool initialized;
        
        HandleList<Mesh> meshes;

        ResourceManager();
    public:
    static ResourceManager& get();
    ~ResourceManager();
    void initialize();

    //Disallow copy and move
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;

    //Mesh
    //Handle<Mesh> createMesh(bool dynamic, )
    //

    };
} // namespace strix
