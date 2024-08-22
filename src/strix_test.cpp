#include <strix/strix.h>
#include <strix/strix_platform.h>
#include <strix/strix_gl.h>
#include <strix/strix_logger.h>

using namespace strix;

int strixMain()
{
    if (!Platform::initOpenGL(3, 3))
    {
        Logger::Error("Failed to initialize OpenGL");
        return -1;
    }
    Window *window = Platform::createWindow(800, 600, "Strix Engine");
    if (!window)
    {
        Logger::Error("Failed to create window");
        return -1;
    }

    while (!Platform::getShouldClose(window))
    {
        Platform::pollEvents(window);

        Platform::swapBuffers(window);
    }

    Platform::destroyWindow(window);

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