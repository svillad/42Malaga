/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:30:06 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:30:06 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

# define NUM_LOG_LEVELS 4
# ifdef LOG
	#define LOG_LEVEL LOG
# else
	#define LOG_LEVEL 1
# endif

typedef enum _LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3,
    OFF = 4
} LogLevel;

class Logger {
private:
	void	(Logger::*actions[NUM_LOG_LEVELS])(std::string msg) const;
	void	debug(std::string msg) const;
	void	info(std::string msg) const;
	void	warning(std::string msg) const;
	void	error(std::string msg) const;

public:
	Logger();
	void	print(LogLevel level, std::string msg) const;
};

#endif
