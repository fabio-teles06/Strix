#pragma once
#include <string>
#include <vector>
#include <memory>
#include "engine_export.hpp"

namespace strix
{
    class STRIX_API Engine
    {
    public:
        Engine();
        ~Engine();

        bool Initialize();
        void Run();
        void Shutdown();
    private:
    bool isRunning = false;

    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    };
}