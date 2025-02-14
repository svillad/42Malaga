#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("unnamed"), grade(150) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Bureaucrat] Default constructor called for " + name + ", grade: " + to_string(grade));
}

Bureaucrat::Bureaucrat(std::string name) : name(name), grade(150) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Bureaucrat] Overload constructor called for " + name + ", grade: " + to_string(grade));
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name), grade(grade) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Bureaucrat] Overload constructor called for " + name + ", grade: " + to_string(grade));
    validateGrade(grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat &b) {
    if (this != &b) {
        name = b.name;
        grade = b.grade;
        logger = b.logger;
    }
    if (logger)
        logger->log(DEBUG,"[Bureaucrat] Copy constructor called for " + b.name + ", grade: " + to_string(grade));
    validateGrade(b.grade);
}

Bureaucrat &Bureaucrat::operator=(const Bureaucrat &b) {
    if (this != &b) {
        name = b.name;
        grade = b.grade;
        logger = b.logger;
    }
    if (logger)
        logger->log(DEBUG,"[Bureaucrat] Copy assignment operator called for " + b.name + ", grade: " + to_string(grade));
    return (*this);
}

Bureaucrat::~Bureaucrat() {
    if (logger)
        logger->log(DEBUG,"[Bureaucrat] Destructor called for " + name);
}

std::string Bureaucrat::getName(void) const {
    return (name);
}

int Bureaucrat::getGrade(void) const {
    return (grade);
}

void Bureaucrat::validateGrade(int grade) const {
    if (grade < 1) {
        if (logger)
            logger->log(WARN, "[Bureaucrat] Grade is too high! Bureaucrat " + name + " cannot have a grade higher than 1 (" + to_string(grade) + ").");
        throw GradeTooHighException(name);
    }
    if (grade > 150) {
        if (logger)
            logger->log(WARN, "[Bureaucrat] Grade is too low! Bureaucrat " + name + " cannot have a grade lower than 150 (" + to_string(grade) + ").");
        throw GradeTooLowException(name);
    }
}

void Bureaucrat::incrementGrade(void) {
    validateGrade(grade - 1);
    grade--;
    if (logger)
        logger->log(INFO, "[Bureaucrat] " + name + " → Grade increased to " + to_string(grade));
}

void Bureaucrat::decrementGrade(void) {
    validateGrade(grade + 1);
    grade++;
    if (logger)
        logger->log(INFO, "[Bureaucrat] " + name + " → Grade decreased to " + to_string(grade));
}

void Bureaucrat::setLogger(ILogger* log) {
    logger = log;
    if (logger)
        logger->log(DEBUG, "[Bureaucrat] Logger initialized in " + name);
}

Bureaucrat::GradeTooHighException::GradeTooHighException(const std::string& name) {
    message = "Grade is too high! " + name + " cannot have a grade higher than 1.";
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
    return message.c_str();;
}

Bureaucrat::GradeTooLowException::GradeTooLowException(const std::string& name) {
    message = "Grade is too low! " + name + " cannot have a grade lower than 150.";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
    return message.c_str();
}

std::ostream& operator<<(std::ostream &stream, const Bureaucrat &b) {
	stream << b.getName()  << ", bureaucrat grade " << b.getGrade();
	return ((stream));
}
