#ifndef PRESIDENTIALPARDON_HPP
#define PRESIDENTIALPARDON_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include "Bureaucrat.hpp"
# include "AForm.hpp"
# include <iostream>
# include <string>

# define DEFAULT_SIGN_PDTE 25
# define DEFAULT_EXEC_PDTE 5

class Bureaucrat;

class PresidentialPardonForm : public AForm {
protected:
    std::string target;

public:
    PresidentialPardonForm();
    PresidentialPardonForm(std::string target);
    PresidentialPardonForm(std::string target, std::string name);

    PresidentialPardonForm(const PresidentialPardonForm &f);
    PresidentialPardonForm& operator=(const PresidentialPardonForm &f);
    virtual ~PresidentialPardonForm();

    virtual void execute(Bureaucrat const &executor) const;

};

#endif
