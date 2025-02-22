/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:25:44 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:25:47 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
#define FORM_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include "Bureaucrat.hpp"
# include <iostream>
# include <string>

class Bureaucrat;

class Form {
protected:
	const std::string name;
	bool  isSigned;
	const int signGrade;
	const int execGrade;
	ILogger *logger;


public:
	Form();
	Form(std::string name);
	Form(std::string name, int grade);
	Form(const Form &f);
	Form& operator=(const Form &f);
	virtual ~Form();

	const std::string getName(void) const;
	bool getIsSigned(void)const;
	int getSignGrade(void)const;
	int getExecGrade(void)const;

	void validateGrade(int grade) const;
	void validateSignGrade(const Bureaucrat &b) const;
	void validateExecGrade(const Bureaucrat &b) const;
	void beSigned(const Bureaucrat &b);

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
				GradeTooLowException();
				virtual ~GradeTooLowException() throw() {}
				virtual const char* what(void) const throw();
	};

	class FormSignedException : public std::exception {
		private: std::string message;
		public:	FormSignedException();
				virtual ~FormSignedException() throw() {}
				virtual const char* what(void) const throw();
	};
};

std::ostream& operator<<(std::ostream &stream, const Form &f);

#endif
