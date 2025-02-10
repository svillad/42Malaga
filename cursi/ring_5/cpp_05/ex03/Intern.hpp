#ifndef INTERN_HPP
#define INTERN_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include "AForm.hpp"
# include "ShrubberyCreationForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "PresidentialPardonForm.hpp"
# include <iostream>
# include <string>

class Intern {
protected:
	static const int FORM_NUM = 3;
	std::string availableForms[FORM_NUM];
    AForm* (*formCreators[FORM_NUM])(const std::string&);
	ILogger *logger;

public:
	Intern();
	Intern(const Intern &b);
	Intern& operator=(const Intern &b);
	virtual ~Intern();

	AForm* makeForm(const std::string formName, const std::string target);

    void setLogger(ILogger* log);
};

AForm* createShrubberyCreationForm(const std::string& target);
AForm* createRobotomyRequestForm(const std::string& target);
AForm* createPresidentialPardonForm(const std::string& target);

#endif
