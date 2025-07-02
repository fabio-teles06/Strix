#pragma once


#ifdef _WIN32
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#else
#error "Unsuported platform"
#endif // _WIN32


#ifdef PLATFORM_WINDOWS
#ifdef STRIX_ENGINE_EXPORTS
#define STRIX_API __declspec(dllexport)
#else
#define STRIX_API __declspec(dllimport)
#endif // STRIX_EXPORTS
#elif defined(PLATFORM_LINUX)
#ifdef STRIX_ENGINE_EXPORTS
#define STRIX_API __attribute__((visibility("default")))
#else
#define STRIX_API
#endif // STRIX_ENGINE_EXPORTS
#else
#error "Unsupported platform for STRIX_API"
#endif // PLATFORM_WINDOWS

