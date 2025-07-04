#include <strix/strix.h>
#include <strix/module.h>
#include <strix/strix_gl.h>
#include <strix/resource_manager.h>

strix::Handle<strix::Mesh> cube;

void onStart()
{
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

    strix::ResourceManager &resourceManager = strix::ResourceManager::get();

    cube = resourceManager.createMesh(false, strix::MeshData::getPrimitiveCube());
}

void onUpdate(float delta)
{
    // Atualizações do jogo aqui
}

void onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(cube->vao);
    glDrawElements(cube->glPrimitive, cube->indexCount, cube->indexSize == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void onStop()
{
}