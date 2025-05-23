/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ILogger.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:25:26 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:25:27 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
