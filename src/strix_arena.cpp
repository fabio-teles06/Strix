#include <strix/strix_arena.h>
#include <strix/strix_platform.h>
#include <strix/strix.h>
#include <strix/strix_logger.h>
#include <math.h>

namespace strix
{

    Arena::Arena() : capacity(0), used(0), data(nullptr) {}

    Arena::Arena(size_t capacity)
    {
        initialize(capacity);
    }

    Arena::Arena(Arena &&other)
    {
        this->~Arena();

        capacity = other.capacity;
        used = other.used;
        data = other.data;

        other.data = nullptr;
        other.used = 0;
        other.capacity = 0;
    }

    Arena::~Arena()
    {
        Platform::freeMemory(data);
    }

    void Arena::initialize(size_t initialSize)
    {
        capacity = initialSize;
        used = 0;
        if (initialSize > 0)
        {
            data = (char *)Platform::getMemory(capacity);
        }
        else
        {
            data = nullptr;
        }
    }

    char *Arena::pushSize(size_t size)
    {
        if (used + size >= capacity)
        {
            size_t newCapacity = 2 * (capacity + size);

            newCapacity = (newCapacity >> 1) | newCapacity;
            newCapacity = (newCapacity >> 2) | newCapacity;
            newCapacity = (newCapacity >> 4) | newCapacity;
            newCapacity = (newCapacity >> 8) | newCapacity;
            newCapacity = (newCapacity >> 16) | newCapacity;
            newCapacity = (newCapacity >> 32) | newCapacity;
            newCapacity++;

            data = (char *)Platform::resizeMemory(data, newCapacity);
            capacity = newCapacity;
        }

        char *memPtr = data + used;
        used += size;
        return memPtr;
    }

    inline void Arena::reset() { used = 0; }

    inline size_t Arena::getCapacity() const { return capacity; }

    inline size_t Arena::getUsed() const { return used; }

    const char *Arena::getData() const { return data; }
}