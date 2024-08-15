#include <strix/strix.h>
#include <strix/strix_platform.h>

int strixMain()
{
    strix::Platform platform;
    strix::Platform::initOpenGL(3, 3);
    strix::Window *window = platform.createWindow(800, 600, "Strix Engine");

    while (!platform.getShouldClose(window))
    {
        platform.pollEvents(window);

        platform.swapBuffers(window);
    }

    return 0;
}

#ifdef PLATFORM_WINDOWS
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return strixMain();
}
#endif

int main(int argc, int argv)
{
    return strixMain();
}