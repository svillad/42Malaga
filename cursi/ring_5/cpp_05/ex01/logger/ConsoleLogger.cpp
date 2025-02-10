#include "ConsoleLogger.hpp"

ConsoleLogger::ConsoleLogger() {}

ConsoleLogger::~ConsoleLogger() {}

const char* ConsoleLogger::getColor(LogLevel level) const {
    switch (level) {
        case DEBUG: return COLOR_DEBUG;
        case INFO: return COLOR_INFO;
        case WARN: return COLOR_WARN;
        case ERROR: return COLOR_ERROR;
        default: return COLOR_RESET;
    }
}

void ConsoleLogger::log(LogLevel level, const std::string& msg) {
    if (level >= LOG_LEVEL) {
        std::cout << getColor(level) << "[ " << ILogger::getLevelName(level) << " ]"
                  << COLOR_RESET << " " << msg << std::endl;
    }
}