#ifndef STRIX_ARENA_H
#define STRIX_ARENA_H

#include <strix/strix.h>

#define KILOBYTE(value) (size_t) ((value) * 1024LL)
#define MEGABYTE(value) (KILOBYTE(value) * 1024LL)
#define GIGABYTE(value) (MEGABYTE(value) * 1024LL)

namespace strix
{
    class STRIX_API Arena
    {
        size_t capacity;
        size_t used;
        char* data;

        public:

        Arena();
        Arena(size_t capacity);
        Arena(Arena&& other);
        ~Arena();

        void initialize(size_t initialSize);
        char* pushSize(size_t size);
        void reset();
        size_t getCapacity() const;
        size_t getUsed() const;
        const char* getData() const;
    };
}

#endif // STRIX_ARENA_H