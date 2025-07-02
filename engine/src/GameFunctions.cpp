#include <engine.hpp>
#include <engine_export.hpp>

static strix::Engine* g_engine = nullptr;

extern "C" {
    STRIX_API strix::Engine* CreateEngine() {
        if (g_engine == nullptr) {
            g_engine = new strix::Engine();
        }
        return g_engine;
    }

    STRIX_API void DestroyEngine() {
        if (g_engine != nullptr) {
            delete g_engine;
            g_engine = nullptr;
        }
    }

    STRIX_API bool InitializeEngine() {
        if (g_engine == nullptr) {
            return false; // Engine not created
        }
        return g_engine->Initialize();
    }

    STRIX_API void RunEngine() {
        if (g_engine != nullptr && g_engine->Initialize()) {
            g_engine->Run();
        }
    }

    STRIX_API void ShutdownEngine() {
        if (g_engine != nullptr) {
            g_engine->Shutdown();
        }
    }
}