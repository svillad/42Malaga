/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:36 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:45:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Intern] Default constructor called");

    availableForms[0] = "ShrubberyCreationForm";
    availableForms[1] = "RobotomyRequestForm";
    availableForms[2] = "PresidentialPardonForm";

    formCreators[0] = &createShrubberyCreationForm;
    formCreators[1] = &createRobotomyRequestForm;
    formCreators[2] = &createPresidentialPardonForm;
}

Intern::Intern(const Intern &i) {
    if (this != &i) {
        logger = i.logger;
    }
    if (logger)
        logger->log(DEBUG,"[Intern] Copy constructor called");
}

Intern &Intern::operator=(const Intern &i) {
    if (this != &i) {
        logger = i.logger;
    }
    if (logger)
        logger->log(DEBUG,"[Intern] Copy assignment operator called");
    return (*this);
}

Intern::~Intern() {
    if (logger)
        logger->log(DEBUG,"[Intern] Destructor called");
}

AForm* Intern::makeForm(const std::string formName, const std::string target) {
    AForm *form = NULL;
    for (int i = 0; i < FORM_NUM; i++) {
        if (formName == availableForms[i]) {
            std::cout << "Intern creates " << formName << std::endl;
            if (logger)
                logger->log(DEBUG, "[Intern] Intern creates " + formName + " to " + target);
            form = formCreators[i](target);
            form->setLogger(logger);
            return form;
        }
    }
    std::cout << "Error: Form " << formName << " does not exist!" << std::endl;
    if (logger)
        logger->log(ERROR, "[Intern] Form " + formName + " does not exist!: ");
    return form;
}

void Intern::setLogger(ILogger* log) {
    logger = log;
    if (logger)
        logger->log(DEBUG, "[Intern] Logger initialized in intern");
}


AForm* createShrubberyCreationForm(const std::string& target) {
    return new ShrubberyCreationForm(target);
}

AForm* createRobotomyRequestForm(const std::string& target) {
    return new RobotomyRequestForm(target);
}

AForm* createPresidentialPardonForm(const std::string& target) {
    return new PresidentialPardonForm(target);
}

