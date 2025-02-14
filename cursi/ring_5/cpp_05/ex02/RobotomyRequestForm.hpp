#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include "Bureaucrat.hpp"
# include "AForm.hpp"
# include <iostream>
# include <cstdlib>
# include <string>

# define DEFAULT_SIGN_ROBOT 72
# define DEFAULT_EXEC_ROBOT 45

class Bureaucrat;

class RobotomyRequestForm : public AForm {
protected:
    std::string target;

public:
    RobotomyRequestForm();
    RobotomyRequestForm(std::string target);
    RobotomyRequestForm(std::string target, std::string name);

    RobotomyRequestForm(const RobotomyRequestForm &f);
    RobotomyRequestForm& operator=(const RobotomyRequestForm &f);
    virtual ~RobotomyRequestForm();

    virtual void execute(Bureaucrat const &executor) const;

};

#endif
