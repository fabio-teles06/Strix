#ifndef STRIX_PLATFORM_H
#define STRIX_PLATFORM_H

#ifdef PLATFORM_WINDOWS
#include <windows.h>
#include <windowsx.h>
#endif

#ifdef STRIX_ENGINE_EXPORTS
#define STRIX_PLATFORM_API __declspec(dllexport)
#else
#define STRIX_PLATFORM_API __declspec(dllimport)
#endif

namespace strix
{
    struct Window;
    struct Module;

    struct STRIX_PLATFORM_API Platform final
    {
        //Basic window functions   
        static Window *createWindow(int32 width, int32 height, const char *title);
        static void destroyWindow(Window *window);
        static void pollEvents(Window *window);
        static bool getShouldClose(Window *window);
        static void setShouldClose(Window *window, bool shouldClose);
        static int getTime();
        //graphics
        static bool initOpenGL(int32 major, int32 minor, int32 colorBits = 32, int32 depthBits = 24);
        static void swapBuffers(Window *window);
        //dynamic module handling
        static Module* loadModule(const char* path);
        static bool unloadModule(Module* module);
        static void* getModuleFunction(Module* module, const char* name);
        //Memory management
        static void* getMemory(size_t size);
        static void* resizeMemory(void* memory, size_t);
        static void freeMemory(void* memory);
    };
}

#endif // STRIX_PLATFORM_H