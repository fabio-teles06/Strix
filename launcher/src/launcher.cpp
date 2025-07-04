#include <strix/strix.h>
#include <strix/logger.h>
#include <strix/platform.h>
#include <strix/strix_gl.h>
#include <strix/module.h>
#include <strix/resource_manager.h>

#include <iostream>
#include <chrono>
#include <string>

strix::Module *gameModule = nullptr;
strix::STRIX_GAME_CALLBACK_ONSTART onGameStart = nullptr;
strix::STRIX_GAME_CALLBACK_ONUPDATE onGameUpdate = nullptr;
strix::STRIX_GAME_CALLBACK_ONRENDER onGameRender = nullptr;
strix::STRIX_GAME_CALLBACK_ONSTOP onGameStop = nullptr;

void loadGame() {
    std::string gamePath = "Game.dll"; // Adjust the path as needed

    gameModule = strix::Platform::loadModule(gamePath.c_str());
    if (!gameModule) {
        strix::Logger::Error("Failed to load game module: %s", gamePath.c_str());
        return;
    }

    onGameStart = (strix::STRIX_GAME_CALLBACK_ONSTART)strix::Platform::getModuleFunction(gameModule, "onStart");
    onGameUpdate = (strix::STRIX_GAME_CALLBACK_ONUPDATE)strix::Platform::getModuleFunction(gameModule, "onUpdate");
    onGameRender = (strix::STRIX_GAME_CALLBACK_ONRENDER)strix::Platform::getModuleFunction(gameModule, "onRender");
    onGameStop = (strix::STRIX_GAME_CALLBACK_ONSTOP)strix::Platform::getModuleFunction(gameModule, "onStop");
}

int strixMain(){
    if(!strix::Platform::initOpenGL(3, 3)){
        strix::Logger::Error("Failed to initialize OpenGL");
        return -1;
    }

    strix::Window *window = strix::Platform::createWindow(800, 600, "Strix Launcher");

    if (!window) {
        strix::Logger::Error("Failed to create window");
        return -1;
    }

    strix::Platform::setShouldClose(window, false);
    
    //init Renderer

    strix::ResourceManager::get().initialize();
    //Renderer::initialize();
    strix::ResourceManager& resourceManager = strix::ResourceManager::get();

    loadGame();
    onGameStart();
    auto lastTime = std::chrono::high_resolution_clock::now();
    while (!strix::Platform::getShouldClose(window)){
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = now - lastTime;
        lastTime = now;

        strix::Platform::pollEvents(window);

        onGameUpdate(delta.count());
        onGameRender();
        
        strix::Platform::swapBuffers(window);
    }
    onGameStop();

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