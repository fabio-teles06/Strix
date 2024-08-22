#include <strix/strix.h>
#include <strix/strix_game.h>
#include <strix/strix_logger.h>
#include <strix/strix_gl.h>
#include <strix/strix_platform.h>

#include <math.h>

float b = 0.0f;
float vertices[] = {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.5f, 0.5f,
    -0.5f, 0.5f};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0};

unsigned int vao, vbo, ebo;
unsigned int shaderProgram;

void onStart()
{
    strix::Logger::Info("onStart");

    glClearColor(0.0f, 0.0f, b, 1.0f);

    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec2 aPos;\n"
                                     "out vec3 vertex_pos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
                                     "   vertex_pos = vec3(aPos, 0.0);\n"
                                     "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "in vec3 vertex_pos;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(vertex_pos.x, vertex_pos.y, 0.2f, 1.0f);\n"
                                       "}\n\0";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);
}

void onUpdate(float deltaTime)
{
    // normalized sin wave
    b = (sin((float)strix::Platform::getTime() / 1000) + 1) / 2;

    glClearColor(0.0f, 0.0f, b, 1.0f);
}

void onRender()
{

    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(vao);
    glEnableVertexArrayAttrib(vao, 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void onStop()
{
    strix::Logger::Info("onStop");

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shaderProgram);
}