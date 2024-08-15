#ifndef STRIX_H
#define STRIX_H

#ifdef _WIN32
#define PLATFORM_WINDOWS
#endif

#ifdef PLATFORM_WINDOWS
#ifdef STRIX_EXPORTS
#define STRIX_API __declspec(dllexport)
#else
#define STRIX_API __declspec(dllimport)
#endif // STRIX_EXPORTS
#else
#define STRIX_API
#endif // PLATFORM_WINDOWS

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

#endif // STRIX_H