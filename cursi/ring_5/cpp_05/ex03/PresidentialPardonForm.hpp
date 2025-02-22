/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:50 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:45:50 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
