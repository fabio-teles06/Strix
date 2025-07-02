#include <strix/strix.h>
#include <strix/strix_game.h>
#include <strix/strix_logger.h>
#include <strix/strix_platform.h>
#include <strix/strix_renderer.h>

//just for testing
#include <strix/strix_gl.h>

strix::Mesh mesh;

void onStart()
{
    strix::Logger::set_log_level(strix::LogLevel::INFO_LOG);
    strix::Logger::Info("Starting game");
    //create a quad
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    strix::Renderer::createMesh(&mesh, vertices, 12, indices, 6);
}

void onUpdate(float deltaTime)
{
    //log error of opengl
}

void onRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    strix::Renderer::drawMesh(mesh, strix::Renderer::getDefaultShaderProgram());
}

void onStop()
{
}