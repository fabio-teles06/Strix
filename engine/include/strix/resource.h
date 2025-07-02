#pragma once
#include <strix/strix.h>
#include <string>

namespace strix
{
    class Resource
    {
    public:
        Resource();
        ~Resource();

        void Load(const std::string& path);
        void Unload();

    private:
        std::string m_path;
        // Other resource data
    };
} // namespace strix
