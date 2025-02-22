/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConsoleLogger.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:25:13 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:25:14 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSOLE_LOGGER_HPP
#define CONSOLE_LOGGER_HPP

#include "ILogger.hpp"
#include <iostream>

// ANSI codes for terminal colors
#define COLOR_RESET   "\e[0m"
#define COLOR_DEBUG   "\e[1;34m"  // Blue
#define COLOR_INFO    "\e[1;32m"  // Green
#define COLOR_WARN    "\e[1;33m"  // Yellow
#define COLOR_ERROR   "\e[1;31m"  // Red

class ConsoleLogger : public ILogger {
private:
    const char* getColor(LogLevel level) const;

public:
	ConsoleLogger();
    ~ConsoleLogger();
    void log(LogLevel level, const std::string& msg);
};

#endif
