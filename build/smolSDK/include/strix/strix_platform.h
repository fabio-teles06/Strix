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

    struct STRIX_PLATFORM_API Platform final
    {
        static Window *createWindow(int32 width, int32 height, const char *title);
        static void destroyWindow(Window *window);
        static bool initOpenGL(int32 major, int32 minor, int32 colorBits = 32, int32 depthBits = 24);
        static void pollEvents(Window *window);
        static void swapBuffers(Window *window);
        static bool getShouldClose(Window *window);
        static void setShouldClose(Window *window, bool shouldClose);
        static int getTime();
    };
}

#endif // STRIX_PLATFORM_H