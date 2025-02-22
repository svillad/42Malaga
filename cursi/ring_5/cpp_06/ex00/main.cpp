/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:21:17 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:21:18 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./convert <literal>" << std::endl;
        return 1;
    }

    ILogger* logger = NULL;

    #ifdef LOG_MODE_CONSOLE
        logger = new ConsoleLogger();
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: Console" << std::endl;
    #elif defined(LOG_MODE_FILE)
        logger = new FileLogger("logs.log");
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: File" << std::endl;
    #else
        std::cerr << "[  ERROR  ] No valid LOG_MODE specified!" << std::endl;
        return 1;
    #endif
    logger->log(DEBUG, "[main] New program execution");

    ScalarConverter::setLogger(logger);
    ScalarConverter::convert(argv[1]);

    delete logger;
    return 0;
}
