#include "strix/logger.h"

namespace strix
{
    LogLevel Logger::m_logLevel = LogLevel::INFO_LOG;
    std::mutex Logger::m_log_mutex;
}