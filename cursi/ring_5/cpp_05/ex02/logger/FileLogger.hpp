#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "ILogger.hpp"
#include <fstream>
#include <ctime>

class FileLogger : public ILogger {
private:
    std::ofstream file;
    std::string getTimestamp() const;
    
public:
    FileLogger(const std::string& filename);
    ~FileLogger();
    void log(LogLevel level, const std::string& msg);
};

#endif
