#include "Form.hpp"

Form::Form() : name("unnamed"), isSigned(false), signGrade(1), execGrade(1) {
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Form] Default constructor called for " + name +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

Form::Form(std::string name) : name(name), isSigned(false), signGrade(1), execGrade(1){
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Form] Overload constructor called for " + name +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

Form::Form(std::string name, int grade) : name(name), isSigned(false), signGrade(grade), execGrade(grade){
    FileLogger logger("logs.log");
    logger.log(DEBUG, "[Form] Overload constructor called for " + name +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
    validateGrade(grade);
}

Form::Form(const Form &f) : signGrade(f.signGrade), execGrade(f.execGrade) {
    if (this != &f) {
        name      = f.name;
        isSigned  = f.isSigned;
        logger    = f.logger;
    }
    if (logger)
        logger->log(DEBUG,"[Form] Copy constructor called for " + name +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
}

Form &Form::operator=(const Form &f) {
    if (this != &f) {
        name      = f.name;
        isSigned  = f.isSigned;
        logger    = f.logger;
    }
    if (logger)
        logger->log(DEBUG,"[Form] Copy assignment operator called for " + name +
                      ", signed: " + to_string(isSigned) +
                      ", sign grade: " + to_string(signGrade) +
                      ", exec grade: " + to_string(execGrade));
    return (*this);
}

Form::~Form() {
    if (logger)
        logger->log(DEBUG,"[Form] Destructor called for " + name);
}

std::string Form::getName(void) const {
    return (name);
}

bool Form::getIsSigned(void) const {
    return (isSigned);
}

int Form::getSignGrade(void) const {
    return (signGrade);
}

int Form::getExecGrade(void) const {
    return (execGrade);
}

void Form::validateGrade(int grade) const {
    if (grade < 1) {
        if (logger)
            logger->log(WARN, "[Form] Grade is too high! Form "+ name + " cannot have a grade higher than 1 to sign/exec.");
        throw GradeTooHighException(name);
    }
    if (grade > 150) {
        if (logger)
            logger->log(WARN, "[Form] Grade is too low! Form" + name + " cannot have a grade lower than 150 to sign/exec.");
        throw GradeTooLowException(name);
    }
}

void Form::validateSignGrade(const Bureaucrat &b) const {
    if (b.getGrade() > signGrade) {
        if (logger)
            logger->log(WARN, "[Form] Grade is too low to sign! Bureaucrat " +
                    b.getName() + "(grade: " + to_string(b.getGrade()) + ") cannot sign the form " +
                    name + + "(grade: " + to_string(signGrade) + ").");
        throw GradeTooLowException();
    }
}

void Form::validateExecGrade(const Bureaucrat &b) const {
    if (b.getGrade() > execGrade) {
        if (logger)
            logger->log(WARN, "[Form] Grade is too low to exec! Bureaucrat " +
                    b.getName() + "(grade: " + to_string(b.getGrade()) + ") cannot exec the form " +
                    name + + "(grade: " + to_string(execGrade) + ").");
        throw GradeTooLowException();
    }
}

void Form::beSigned(const Bureaucrat &b) {
    validateSignGrade(b);
    if (isSigned) {
        if (logger)
            logger->log(WARN, "[Form] " + name + " couldn't Signed by " + b.getName() + " because the form is already signed." );
        throw FormSignedException();
    }
    isSigned = true;
    std::cout << b.getName() << " signed " << name << std::endl;
    if (logger)
        logger->log(INFO, "[Form] " + name + " → Signed by " + b.getName());
}

void Form::setLogger(ILogger* log) {
    logger = log;
    if (logger)
        logger->log(DEBUG, "[Form] Logger initialized in " + name);
}

Form::GradeTooHighException::GradeTooHighException(const std::string& name) {
    message = "Grade is too high! " + name + " cannot have a grade higher than 1.";
}

const char* Form::GradeTooHighException::what() const throw() {
    return message.c_str();;
}

Form::GradeTooLowException::GradeTooLowException(const std::string& name) {
    message = "Grade is too low! " + name + " cannot have a grade lower than 150.";
}

Form::GradeTooLowException::GradeTooLowException() {
    message = "Bureaucrat grade is too low!";
}

const char* Form::GradeTooLowException::what() const throw() {
    return message.c_str();
}

Form::FormSignedException::FormSignedException() {
    message = "Form is already signed!";
}

const char* Form::FormSignedException::what() const throw() {
    return message.c_str();;
}

std::ostream& operator<<(std::ostream &stream, const Form &f) {
	stream << f.getName()
           << ", is signed " << f.getIsSigned()
	       << ", sign grade " << f.getSignGrade()
	       << ", exec grade " << f.getExecGrade();
	return ((stream));
}
