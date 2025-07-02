#pragma once
#include <strix/strix.h>
#include <cstdio>
#include <mutex>

namespace strix
{
    enum class LogLevel
    {
        INFO_LOG,
        WARNING_LOG,
        ERROR_LOG
    };

    class STRIX_API Logger
    {
    private:
        static LogLevel m_logLevel;
        static std::mutex m_log_mutex;

    public:
        static void set_log_level(LogLevel logLevel)
        {
            m_logLevel = logLevel;
        }
        
        template<typename... Args>
        static void Info(const char* message, Args... args) {
            if (m_logLevel <= LogLevel::INFO_LOG)
            {
                std::scoped_lock lock(m_log_mutex);
                printf("[INFO]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Warning(const char* message, Args... args) {
            if (m_logLevel <= LogLevel::WARNING_LOG)
            {
                std::scoped_lock lock(m_log_mutex);
                printf("[WARNING]\t");
                printf(message, args...);
                printf("\n");
            }
        }

        template<typename... Args>
        static void Error(const char* message, Args... args) {
            if (m_logLevel <= LogLevel::ERROR_LOG)
            {
                std::scoped_lock lock(m_log_mutex);
                printf("[ERROR]\t");
                printf(message, args...);
                printf("\n");
            }
        }
    };
}