/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:35:20 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:35:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ILogger.hpp"
#include "ConsoleLogger.hpp"
#include "FileLogger.hpp"
#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>

int main() {
    ILogger* logger = NULL;

    #ifdef LOG_MODE_CONSOLE
        logger = new ConsoleLogger();
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: Console" << std::endl;
    #elif defined(LOG_MODE_FILE)
        logger = new FileLogger("logs.log");
        std::cout << COLOR_DEBUG << "[  DEBUG  ] " << COLOR_RESET << "Logging mode: File" << std::endl;
    #else
        std::cerr << COLOR_ERROR << "[  ERROR  ] " << COLOR_RESET << "No valid LOG_MODE specified!" << COLOR_RESET << std::endl;
        return 1;
    #endif
    logger->log(DEBUG, "[main] New program execution");

    try {
        std::cout << "\n---------- Bureaucrat's tests ----------" << std::endl;
        Bureaucrat b1("Jesica", 1);
        b1.setLogger(logger);
        Bureaucrat b2("Sebas", 150);
        b2.setLogger(logger);
        std::cout << b1 << std::endl;
        std::cout << b2 << std::endl;

        b1.decrementGrade();
        b2.incrementGrade();
        std::cout << b1 << std::endl;
        std::cout << b2 << std::endl;

        std::cout << "\n---------- ShrubberyCreationForm's tests ----------" << std::endl;
        ShrubberyCreationForm f1("file");
        f1.setLogger(logger);
        std::cout << f1 << std::endl;
        b1.executeForm(f1);
        b1.signForm(f1);
        b1.signForm(f1);
        b2.signForm(f1);

        b1.executeForm(f1);
        b2.executeForm(f1);

        std::cout << "\n---------- RobotomyRequestForm's tests ----------" << std::endl;
        RobotomyRequestForm f2("Robotina");
        f2.setLogger(logger);
        std::cout << f2 << std::endl;
        b1.executeForm(f2);
        b1.signForm(f2);
        b1.signForm(f2);
        b2.signForm(f2);

        b1.executeForm(f2);
        b2.executeForm(f2);

        std::cout << "\n---------- PresidentialPardonForm's tests ----------" << std::endl;
        PresidentialPardonForm f3("X Æ A-12");
        f3.setLogger(logger);
        std::cout << f3 << std::endl;
        b1.executeForm(f3);
        b1.signForm(f3);
        b1.signForm(f3);
        b2.signForm(f3);

        b1.executeForm(f3);
        b2.executeForm(f3);

        std::cout << "\n---------- Exception's test ----------" << std::endl;
        Bureaucrat b3("Juan", 10);
        b3.setLogger(logger);
        for (int i = 0; i < 200; i++) {
            b3.incrementGrade();
        }
        std::cout << b3 << std::endl;

    } catch (const std::exception &e) {
        logger->log(ERROR, "[main] Exception: " + std::string(e.what()));
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    delete logger;
    return 0;
}
