/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:35:27 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:35:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm() {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[PresidentialPardonForm] Default constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

PresidentialPardonForm::PresidentialPardonForm(std::string target)
    : AForm("PresidentialForm", DEFAULT_SIGN_PDTE, DEFAULT_EXEC_PDTE), target(target) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[PresidentialPardonForm] Overload constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

PresidentialPardonForm::PresidentialPardonForm(std::string target, std::string name)
    : AForm(name, DEFAULT_SIGN_PDTE, DEFAULT_EXEC_PDTE), target(target) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[PresidentialPardonForm] Overload constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &f)
    : AForm(f) {
    if (this != &f) {
        target = f.target;
    }
    if (logger)
        logger->log(DEBUG,"[PresidentialPardonForm] Copy constructor called for " + name +
                      ", target: " + target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &f) {
    if (this != &f) {
        AForm::operator=(f);
        target = f.target;
    }
    if (logger)
        logger->log(DEBUG,"[PresidentialPardonForm] Copy assignment operator called for " + name +
                      ", target: " + target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
    return (*this);
}

PresidentialPardonForm::~PresidentialPardonForm() {
    if (logger)
        logger->log(DEBUG,"[PresidentialPardonForm] Destructor called for " + name);
}

void PresidentialPardonForm::execute(Bureaucrat const &b) const {
    validateExecGrade(b);
    if (!isSigned) {
        if (logger)
            logger->log(WARN, "[PresidentialPardonForm] " + name + " could not be executed by " + b.getName() + " because it has not been signed" );
        throw FormSignedException(false);
    }

    std::cout << b.getName() << " execute " << name << std::endl;
    std::cout << target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
    if (logger) {
        logger->log(INFO, "[PresidentialPardonForm] " + target + " has been pardoned by Zaphod Beeblebrox. ");
        logger->log(INFO, "[PresidentialPardonForm] " + name + " → Executed by " + b.getName());
    }
}
