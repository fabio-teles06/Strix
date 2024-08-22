#include <strix/strix.h>
#include <strix/strix_logger.h>
#include <strix/strix_platform.h>
#include <strix/strix_gl.h>
#include <strix/strix_game.h>

#include <iostream>
#include <string>

int strixMain()
{
    if (!strix::Platform::initOpenGL(3, 3))
    {
        strix::Logger::Error("Failed to initialize OpenGL");
        return -1;
    }

    strix::Window *window = strix::Platform::createWindow(800, 600, "Strix Engine");

    if (!window)
    {
        strix::Logger::Error("Failed to create window");
        return -1;
    }

    strix::Platform::setShouldClose(window, false);

    strix::Module *game = strix::Platform::loadModule("libgame.dll");
    strix::STRIX_GAME_CALLBACK_ONSTART onGameStart = (strix::STRIX_GAME_CALLBACK_ONSTART)
        strix::Platform::getModuleFunction(game, strix::STRIX_CALLBACK_NAME_ONSTART);

    strix::STRIX_GAME_CALLBACK_ONUPDATE onGameUpdate = (strix::STRIX_GAME_CALLBACK_ONUPDATE)
        strix::Platform::getModuleFunction(game, strix::STRIX_CALLBACK_NAME_ONUPDATE);

    strix::STRIX_GAME_CALLBACK_ONRENDER onGameRender = (strix::STRIX_GAME_CALLBACK_ONRENDER)
        strix::Platform::getModuleFunction(game, strix::STRIX_CALLBACK_NAME_ONRENDER);

    strix::STRIX_GAME_CALLBACK_ONSTOP onGameStop = (strix::STRIX_GAME_CALLBACK_ONSTOP)
        strix::Platform::getModuleFunction(game, strix::STRIX_CALLBACK_NAME_ONSTOP);

    onGameStart();

    while (!strix::Platform::getShouldClose(window))
    {
        strix::Platform::pollEvents(window);

        onGameUpdate(0.0f);
        onGameRender();

        strix::Platform::swapBuffers(window);
    }

    onGameStop();

    strix::Platform::destroyWindow(window);

    return 0;
}

#ifdef PLATFORM_WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return strixMain();
}
#endif

int main(int argc, char **argv)
{
    return strixMain();
}