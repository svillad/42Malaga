/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileLogger.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:38:42 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:38:43 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FileLogger.hpp"

FileLogger::FileLogger(const std::string& filename) {
    file.open(filename.c_str(), std::ios::app);
}

FileLogger::~FileLogger() {
    if (file.is_open()) {
        file.close();
    }
}

std::string FileLogger::getTimestamp() const {
    time_t now = time(0);
    struct tm tstruct;
    char buf[30];

    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "[%Y-%m-%d %H:%M:%S]", &tstruct);  

    return std::string(buf);
}

void FileLogger::log(LogLevel level, const std::string& msg) {
    if (level >= LOG_LEVEL) {
        if (file.is_open()) {
            file << getTimestamp() << " [ " << ILogger::getLevelName(level) << " ] " << msg << std::endl;
        }
    }
}