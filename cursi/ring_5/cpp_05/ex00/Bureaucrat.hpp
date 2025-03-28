/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:13:11 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:13:12 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include <iostream>
# include <sstream>
# include <string>

class Bureaucrat {
protected:
	std::string	name;
	int grade;
	ILogger *logger;

public:
	Bureaucrat();
	Bureaucrat(std::string name);
	Bureaucrat(std::string name, int grade);

	Bureaucrat(const Bureaucrat &b);
	Bureaucrat& operator=(const Bureaucrat &b);
	virtual ~Bureaucrat();

	std::string	getName(void) const;
	int	getGrade(void) const;

	void validateGrade(int grade) const;
	void incrementGrade(void);
	void decrementGrade(void);

    void setLogger(ILogger* log);

	class GradeTooHighException : public std::exception {
		private: std::string message;
		public:	GradeTooHighException(const std::string& name);
				virtual ~GradeTooHighException() throw() {}
				virtual const char* what(void) const throw();
	};

	class GradeTooLowException : public std::exception {
		private: std::string message;
		public:	GradeTooLowException(const std::string& name);
				virtual ~GradeTooLowException() throw() {}
				virtual const char* what(void) const throw();
	};
};

std::ostream& operator<<(std::ostream &stream, const Bureaucrat &b);

template<typename T>
std::string to_string(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

#endif
