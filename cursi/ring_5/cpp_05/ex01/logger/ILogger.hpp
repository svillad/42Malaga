/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ILogger.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:25:29 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:25:30 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>

typedef enum _LogLevel {
    DEBUG = 0,
    INFO  = 1,
    WARN  = 2,
    ERROR = 3,
    OFF   = 4
} LogLevel;

#define LOG_LEVEL_DEBUG  DEBUG
#define LOG_LEVEL_INFO   INFO
#define LOG_LEVEL_WARN   WARN
#define LOG_LEVEL_ERROR  ERROR
#define LOG_LEVEL_OFF    OFF

#ifndef LOG_LEVEL
    #define LOG_LEVEL LOG_LEVEL_INFO
#endif

class ILogger {
public:
    virtual ~ILogger();
    virtual void log(LogLevel level, const std::string& msg) = 0;
    static const char* getLevelName(LogLevel level);
};
#endif
