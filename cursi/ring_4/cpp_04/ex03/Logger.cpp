/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:30:02 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:30:04 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Logger.hpp"

Logger::Logger() {
	actions[0] = &Logger::debug;
	actions[1] = &Logger::info;
	actions[2] = &Logger::warning;
	actions[3] = &Logger::error;
}

void Logger::debug(std::string msg) const {
	std::cout << "\e[1;34m[  DEBUG  ]\e[0m ";
	std::cout << msg << std::endl;
}

void Logger::info(std::string msg) const {
	if(LOG_LEVEL != OFF)
		std::cout << "\e[1;32m[  INFO   ]\e[0m ";
	std::cout << msg << std::endl;
}

void Logger::warning(std::string msg) const {
	std::cout << "\e[1;33m[ WARNING ]\e[0m ";
	std::cout << msg << std::endl;
}

void Logger::error(std::string msg) const {
	std::cout << "\e[1;31m[  ERROR  ]\e[0m ";
	std::cout << msg << std::endl;
}

void Logger::print(LogLevel level, std::string msg) const {
	if ((int)level >= LOG_LEVEL || (level == INFO && LOG_LEVEL == OFF))
		(this->*actions[(int)level])(msg);
}
