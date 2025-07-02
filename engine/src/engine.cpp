#include <engine.hpp>
#include <chrono>
#include <thread>

using namespace strix;

Engine::Engine() {}
Engine::~Engine() {}

bool Engine::Initialize() {
    // Initialization logic here
    isRunning = true;
    return true; // Return true if initialization is successful
}

void Engine::Run() {
    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();

    while (isRunning){
        auto now = clock::now();
        std::chrono::duration<float> delta = now - lastTime;
        lastTime = now;

        ProcessEvents();
        Update(delta.count());
        Render();

        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Roughly 60 FPS
    }
}

void Engine::Shutdown() {
    // Cleanup logic here
    isRunning = false;
}

void Engine::ProcessEvents() {
    // Handle input and other events here
    // This is where you would check for user input, window events, etc.
}

void Engine::Update(float deltaTime) {
    // Update game state here
    // This is where you would update your game objects, physics, etc.
}

void Engine::Render() {
    // Render the scene here
    // This is where you would draw your game objects to the screen.
}