#pragma once
#include <strix/strix.h>

#define KILOBYTE(x) (size_t)((x) * 1024LL)
#define MEGABYTE(x) (size_t)(KILOBYTE(x) * 1024LL)
#define GIGABYTE(x) (size_t)(MEGABYTE(x) * 1024LL)

namespace strix
{
    class STRIX_API Arena
    {
        size_t capacity;
        size_t used;
        char *data;

    public:
        Arena();
        Arena(size_t capacity);
        Arena(Arena &&other);
        ~Arena();

        void initialize(size_t initialSize);
        char *pushSize(size_t size);
        void reset();

        size_t getCapacity() const;
        size_t getUsed() const;
        const char *getData() const;
    };
}
