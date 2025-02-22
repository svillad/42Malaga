/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:46:02 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:46:03 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm(), target("target") {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[ShrubberyCreationForm] Default constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
    : AForm("ShrubberyForm", DEFAULT_SIGN_GRADE, DEFAULT_EXEC_GRADE), target(target+"_shrubbery") {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[ShrubberyCreationForm] Overload constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string target, std::string name)
    : AForm(name, DEFAULT_SIGN_GRADE, DEFAULT_EXEC_GRADE), target(target+"_shrubbery") {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[ShrubberyCreationForm] Overload constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &f)
    : AForm(f) {
    if (this != &f) {
        target = f.target;
    }
    if (logger)
        logger->log(DEBUG,"[ShrubberyCreationForm] Copy constructor called for " + name +
                      ", target: " + target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &f) {
    if (this != &f) {
        AForm::operator=(f);
        target = f.target;
    }
    if (logger)
        logger->log(DEBUG,"[ShrubberyCreationForm] Copy assignment operator called for " + name +
                      ", target: " + target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
    return (*this);
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
    if (logger)
        logger->log(DEBUG,"[ShrubberyCreationForm] Destructor called for " + name);
}

void ShrubberyCreationForm::execute(Bureaucrat const &b) const {
    validateExecGrade(b);
    if (!isSigned) {
        if (logger)
            logger->log(WARN, "[ShrubberyCreationForm] " + name + " could not be executed by " + b.getName() + " because it has not been signed" );
        throw FormSignedException(false);
    }
    std::ofstream file(target.c_str(), std::ios::app);
    if (!file.is_open()) {
        if (logger)
            logger->log(ERROR, "[ShrubberyCreationForm] " + name + " Error opening file: " + target);
        throw std::ios_base::failure("unable to open file " + target);
    }
    std::cout << b.getName() << " execute " << name << " in file: " << target << std::endl;
    file << "        ccee88oo\n"
         << "     C8O8O8Q8PoOb o8oo  \n"
         << "  dOB69QO8PdUOpugoO9bD  \n"
         << "CgggbU8OU qOp qOdoUOdcb  \n"
         << "   6OuU  /p u gcoUodpP  \n"
         << "      \\\\//  /douUP  \n"
         << "        \\\\////  \n"
         << "         |||/  \n"
         << "         |||  \n"
         << "         |||  \n"
         << "         |||  \n"
         << "    , -=-~  .-^- _  \n"
         << std::endl;
    file.close();
    if (logger)
        logger->log(INFO, "[ShrubberyCreationForm] " + name + " → Executed by " + b.getName() + " in file: " + target);
}
