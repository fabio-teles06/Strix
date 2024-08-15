#include <strix/strix.h>
#include <strix/strix_platform.h>
#include <strix/strix_logger.h>
#include <strix/strix_gl.h>

#include <iostream>

namespace strix
{
    /*
    implementação específica para a plataforma Windows
    usando a API do Windows
    */

    const int STRIX_CLOSE_WINDOW = WM_USER + 1;

    struct Window
    {
        HWND handle;
        bool shouldClose;
        HDC dc;
        HGLRC rc;
    };

    static struct RenderAPIInfo
    {
        enum RenderAPIName
        {
            NONE = 0,
            OPENGL = 1,
        };

        struct OpenGL
        {
            HGLRC sharedContext;
            unsigned int versionMajor;
            unsigned int versionMinor;
            PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
            PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
            int pixelFormatAttribs[16];
            int contextAttribs[16];
        };

        RenderAPIName name;
        OpenGL gl;
    } globalRenderApiInfo;

    LRESULT strixWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CLOSE:
            PostMessageA(hwnd, STRIX_CLOSE_WINDOW, 0, 0);
            break;
        default:
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        }
        return 0;
    }

    Window *Platform::createWindow(int32 width, int32 height, const char *title)
    {
        Logger::Info("Creating window with title: %s", title);
        const char *className = "strixWindowClass";
        HINSTANCE hInstance = GetModuleHandle(NULL);
        WNDCLASSEXA wc = {};

        // Registra a classe caso ela não exista
        if (!GetClassInfoExA(hInstance, className, &wc))
        {
            wc.cbSize = sizeof(WNDCLASSEXA);
            wc.style = CS_OWNDC;
            wc.lpfnWndProc = strixWindowProc;
            wc.hInstance = hInstance;
            wc.hCursor = LoadCursor(NULL, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
            wc.lpszClassName = className;

            if (!RegisterClassExA(&wc))
            {
                Logger::Error("Failed to register window class");
                return nullptr;
            }
        }

        HWND windowHandle = CreateWindowExA(
            0,
            className,
            title,
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT,
            width, height,
            NULL, NULL, hInstance, NULL);

        if (!windowHandle)
        {
            Logger::Error("Failed to create window");
            return nullptr;
        }

        Window *window = new Window();
        window->handle = windowHandle;
        window->shouldClose = false;

        window->dc = GetDC(windowHandle);

        if (globalRenderApiInfo.name == globalRenderApiInfo.OPENGL)
        {
            int pixelFormat;
            int numPixelFormats = 0;
            PIXELFORMATDESCRIPTOR pfd;

            const int *pixelFormatAttribList = (const int *)globalRenderApiInfo.gl.pixelFormatAttribs;
            const int *contextAttribList = (const int *)globalRenderApiInfo.gl.contextAttribs;

            globalRenderApiInfo.gl.wglChoosePixelFormatARB(window->dc,
                                                           pixelFormatAttribList,
                                                           nullptr,
                                                           1,
                                                           &pixelFormat,
                                                           (UINT *)&numPixelFormats);

            if (numPixelFormats <= 0)
            {
                Logger::Error("Unable to find a suitable pixel format");
                return nullptr;
            }

            if (!SetPixelFormat(window->dc, pixelFormat, &pfd))
            {
                Logger::Error("Unable to set a pixel format");
                return nullptr;
            }

            HGLRC sharedContext = globalRenderApiInfo.gl.sharedContext;
            HGLRC rc = globalRenderApiInfo.gl.wglCreateContextAttribsARB(window->dc, sharedContext, contextAttribList);

            bool mustGetGLFunctions = false;
            if (!sharedContext)
            {
                globalRenderApiInfo.gl.sharedContext = rc;
                mustGetGLFunctions = true;
            }

            if (!rc)
            {
                Logger::Error("Unable to create a valid OpenGL context");
                return nullptr;
            }

            window->rc = rc;
            if (!wglMakeCurrent(window->dc, window->rc))
            {
                Logger::Error("Unable to set OpenGL context current");
                return nullptr;
            }

            if (mustGetGLFunctions)
            {
                getOpenGLFunctionPointers();
            }
        }

        return window;
    }

    void Platform::destroyWindow(Window *window)
    {
        if (window)
        {
            if (window->rc)
            {
                wglMakeCurrent(window->dc, NULL);
                wglDeleteContext(window->rc);
            }

            if (window->dc)
            {
                ReleaseDC(window->handle, window->dc);
            }

            if (window->handle)
            {
                DestroyWindow(window->handle);
            }

            delete window;
        }
    }

    void Platform::pollEvents(Window *window)
    {
        MSG msg;
        while (PeekMessageA(&msg, window->handle, 0, 0, PM_REMOVE))
        {
            if (msg.message == STRIX_CLOSE_WINDOW)
            {
                window->shouldClose = true;
                return;
            }

            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    void Platform::swapBuffers(Window *window)
    {
        SwapBuffers(window->dc);
    }

    bool Platform::getShouldClose(Window *window)
    {
        return window->shouldClose;
    }

    void Platform::setShouldClose(Window *window, bool shouldClose)
    {
        window->shouldClose = shouldClose;
    }

    int Platform::getTime()
    {
        return GetTickCount();
    }

    bool Platform::initOpenGL(int32 major, int32 minor, int32 colorBits, int32 depthBits)
    {
        Logger::Info("Initializing OpenGL");
        Window *dummyWindow = createWindow(0, 0, "dummy");

        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR), //  size of this pfd
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA,
            (BYTE)depthBits,
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            (BYTE)colorBits,
            0,
            0,
            PFD_MAIN_PLANE,
            0,
            0, 0, 0};

        int pixelFormat = ChoosePixelFormat(dummyWindow->dc, &pfd);
        if (!pixelFormat)
        {
            Logger::Error("Unable to allocate a pixel format");
            destroyWindow(dummyWindow);
            return false;
        }
        if (!SetPixelFormat(dummyWindow->dc, pixelFormat, &pfd))
        {
            Logger::Error("Unable to set a pixel format");
            destroyWindow(dummyWindow);
            return false;
        }

        HGLRC rc = wglCreateContext(dummyWindow->dc);
        if (!rc)
        {
            Logger::Error("Unable to create a valid OpenGL context");
            destroyWindow(dummyWindow);
            return false;
        }

        if (!wglMakeCurrent(dummyWindow->dc, rc))
        {
            Logger::Error("Unable to set OpenGL context current");
            destroyWindow(dummyWindow);
            return false;
        }

        const int PixelFormatAttribList[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_COLOR_BITS_ARB, colorBits,
            WGL_DEPTH_BITS_ARB, depthBits,
            0};

        const int ContextAttribList[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, major,
            WGL_CONTEXT_MINOR_VERSION_ARB, minor,
            WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0};

        globalRenderApiInfo.name = globalRenderApiInfo.OPENGL;
        globalRenderApiInfo.gl.sharedContext = 0;
        globalRenderApiInfo.gl.versionMajor = major;
        globalRenderApiInfo.gl.versionMinor = minor;
        globalRenderApiInfo.gl.wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        globalRenderApiInfo.gl.wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
        memcpy(globalRenderApiInfo.gl.pixelFormatAttribs, PixelFormatAttribList, sizeof(PixelFormatAttribList));
        memcpy(globalRenderApiInfo.gl.contextAttribs, ContextAttribList, sizeof(ContextAttribList));

        Logger::Info("OpenGL initialized");

        wglMakeCurrent(0, 0);
        wglDeleteContext(rc);
        destroyWindow(dummyWindow);
        return true;
    }

    // TODO: Implementar funções de modificar a janela (titúto, tamanho, etc)

}