#pragma once

#ifdef STRIX_ENGINE_EXPORTS
#define STRIX_GAME_API __declspec(dllimport)
#else
#define STRIX_GAME_API __declspec(dllexport)
#endif // STRIX_EXPORTS

namespace strix
{
    const char *STRIX_CALLBACK_NAME_ONSTART = "onStart";
    const char *STRIX_CALLBACK_NAME_ONUPDATE = "onUpdate";
    const char *STRIX_CALLBACK_NAME_ONRENDER = "onRender";
    const char *STRIX_CALLBACK_NAME_ONSTOP = "onStop";

    typedef void (*STRIX_GAME_CALLBACK_ONSTART)();
    typedef void (*STRIX_GAME_CALLBACK_ONUPDATE)(float);
    typedef void (*STRIX_GAME_CALLBACK_ONRENDER)();
    typedef void (*STRIX_GAME_CALLBACK_ONSTOP)();
}

extern "C"
{
    STRIX_GAME_API void onStart();
    STRIX_GAME_API void onUpdate(float);
    STRIX_GAME_API void onRender();
    STRIX_GAME_API void onStop();
}