/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:45:26 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 15:45:27 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
#define AFORM_HPP

# include "ILogger.hpp"
# include "FileLogger.hpp"
# include "ConsoleLogger.hpp"
# include "Bureaucrat.hpp"
# include <iostream>
# include <string>

class Bureaucrat;

class AForm {
protected:
	const std::string name;
	bool  isSigned;
	const int signGrade;
	const int execGrade;
	ILogger *logger;

public:
	AForm();
	AForm(std::string name);
	AForm(std::string name, int grade);
	AForm(std::string name, int signGrade, int execGrade);
	
	AForm(const AForm &f);
	AForm& operator=(const AForm &f);
	virtual ~AForm();

	const std::string getName(void) const;
	bool getIsSigned(void)const;
	int getSignGrade(void)const;
	int getExecGrade(void)const;

	void validateGrade(int grade) const;
	void validateSignGrade(const Bureaucrat &b) const;
	void validateExecGrade(const Bureaucrat &b) const;
	void beSigned(const Bureaucrat &b);

	virtual void execute(Bureaucrat const &executor) const = 0;

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
		public:	FormSignedException(bool isSigned);
				virtual ~FormSignedException() throw() {}
				virtual const char* what(void) const throw();
	};
};

std::ostream& operator<<(std::ostream &stream, const AForm &f);

#endif
