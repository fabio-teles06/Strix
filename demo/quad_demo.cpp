#include <strix/strix.h>
#include <strix/strix_game.h>
#include <strix/strix_logger.h>
#include <strix/strix_platform.h>
#include <strix/strix_renderer.h>

strix::Mesh *quad_test;

void onStart()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0};

    quad_test = strix::StrixRenderer::createMesh(
        false,
        vertices,
        4,
        indices,
        6,
        nullptr,
        nullptr);
}

void onUpdate(float deltaTime)
{
}

void onRender()
{
    strix::StrixRenderer::clear();

    strix::StrixRenderer::drawMesh(quad_test);
}

void onStop()
{
}