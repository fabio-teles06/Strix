#pragma once

#ifdef _WIN32
#define PLATFORM_WINDOWS
#elif defined(__linux__)
#define PLATFORM_LINUX
#else
#error "Unsupported platform. Please define PLATFORM_WINDOWS or PLATFORM_LINUX."
#endif


#ifdef PLATFORM_WINDOWS
#ifdef STRIX_ENGINE_EXPORTS
#define STRIX_API __declspec(dllexport)
#else
#define STRIX_API __declspec(dllimport)
#endif
#elif defined(PLATFORM_LINUX)
#ifdef STRIX_ENGINE_EXPORTS
#define STRIX_API __attribute__((visibility("default")))
#else
#define STRIX_API
#define STRIX_API
#endif
#else
#error "Unsupported platform. Please define PLATFORM_WINDOWS or PLATFORM_LINUX."
#endif

#include <stdint.h>
typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;
typedef uint8_t uint8;
typedef unsigned char uchar;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;