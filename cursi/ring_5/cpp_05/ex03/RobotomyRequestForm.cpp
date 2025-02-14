#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm() {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[RobotomyRequestForm] Default constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

RobotomyRequestForm::RobotomyRequestForm(std::string target)
    : AForm("RobotomyForm", DEFAULT_SIGN_ROBOT, DEFAULT_EXEC_ROBOT), target(target) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[RobotomyRequestForm] Overload constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

RobotomyRequestForm::RobotomyRequestForm(std::string target, std::string name)
    : AForm(name, DEFAULT_SIGN_ROBOT, DEFAULT_EXEC_ROBOT), target(target) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[RobotomyRequestForm] Overload constructor called for " + name +
                      ", target: " + this->target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &f)
    : AForm(f) {
    if (this != &f) {
        target = f.target;
    }
    if (logger)
        logger->log(DEBUG,"[RobotomyRequestForm] Copy constructor called for " + name +
                      ", target: " + target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &f) {
    if (this != &f) {
        AForm::operator=(f);
        target = f.target;
    }
    if (logger)
        logger->log(DEBUG,"[RobotomyRequestForm] Copy assignment operator called for " + name +
                      ", target: " + target +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
    return (*this);
}

RobotomyRequestForm::~RobotomyRequestForm() {
    if (logger)
        logger->log(DEBUG,"[RobotomyRequestForm] Destructor called for " + name);
}

void RobotomyRequestForm::execute(Bureaucrat const &b) const {
    validateExecGrade(b);
    if (!isSigned) {
        if (logger)
            logger->log(WARN, "[RobotomyRequestForm] " + name + " could not be executed by " + b.getName() + " because it has not been signed" );
        throw FormSignedException(false);
    }

    std::cout << b.getName() << " execute " << name << std::endl;
    std::cout << "* BZZZZZZZZZ... DRRRR... BZZZZT *" << std::endl;
    std::srand(std::time(NULL));
    bool success = (std::rand() % 2 == 0);
    if (success) {
        std::cout << target << " has been robotomized successfully! ✅ 🤖" << std::endl;
        std::cout << "               /(o_o)\\" << std::endl;
        std::cout << "  * Beep Boop! Robotomy Successful! *" << std::endl;
        if (logger)
            logger->log(INFO, "[RobotomyRequestForm] " + target + " has been robotomized successfully. ✅ 🤖");
    } else {
        std::cout << "The robotomy failed on " << target << "! ❌ 🤖" << std::endl;
        std::cout << "           /(x_x)\\" << std::endl;
        std::cout << "  * ERROR! Robotomy Failed! *" << std::endl;
        if (logger)
            logger->log(ERROR, "[RobotomyRequestForm] The robotomy failed on " + target + ". ❌ 🤖");
    }
    if (logger)
        logger->log(INFO, "[RobotomyRequestForm] " + name + " → Executed by " + b.getName());
}
