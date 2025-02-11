#include "ILogger.hpp"

ILogger::~ILogger() {}

const char* ILogger::getLevelName(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG: return " DEBUG ";
        case LOG_LEVEL_INFO:  return " INFO  ";
        case LOG_LEVEL_WARN:  return "WARNING";
        case LOG_LEVEL_ERROR: return " ERROR ";
        default: return "UNKNOWN";
    }
}
