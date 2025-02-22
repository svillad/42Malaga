/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:46:05 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:46:06 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include "Bureaucrat.hpp"
# include "AForm.hpp"
# include <iostream>
# include <string>

# define DEFAULT_SIGN_GRADE 145
# define DEFAULT_EXEC_GRADE 137

class Bureaucrat;

class ShrubberyCreationForm : public AForm {
protected:
    std::string target;

public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(std::string target);
    ShrubberyCreationForm(std::string target, std::string name);

    ShrubberyCreationForm(const ShrubberyCreationForm &f);
    ShrubberyCreationForm& operator=(const ShrubberyCreationForm &f);
    virtual ~ShrubberyCreationForm();

    virtual void execute(Bureaucrat const &executor) const;

};

#endif
