#include <strix/strix.h>
#include <strix/strix_game.h>
#include <strix/strix_logger.h>
#include <strix/strix_gl.h>
#include <strix/strix_platform.h>

void onStart()
{
}

void onUpdate(float deltaTime)
{
    if (strix::Platform::getTime() % 1000 == 0){
        strix::Logger::Info("Time: %d", strix::Platform::getTime());
    }
}

void onRender()
{
}

void onStop()
{
}