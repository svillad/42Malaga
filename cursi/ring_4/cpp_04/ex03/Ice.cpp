/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:50 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:50 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"

Ice::Ice() : AMateria("ice") {
	log.print(DEBUG, "\e[33m[Ice]\e[0m Default constructor called for " + type);
}

Ice::Ice(const Ice &c) : AMateria(c) {
	log.print(DEBUG, "\e[33m[Ice]\e[0m Copy constructor called for " + c.type);
}

Ice &Ice::operator=(const Ice &c) {
	log.print(DEBUG, "\e[33m[Ice]\e[0m Copy assignment operator called for " + c.type);
	if (this != &c) {
		type = c.type;
	}
	return (*this);
}

Ice::~Ice() {
	log.print(DEBUG, "\e[33m[Ice]\e[0m Destructor called for ");
}

AMateria* Ice::clone() const
{
	log.print(DEBUG, "\e[33m[Ice]\e[0m Start clone process");
	AMateria *temp = new Ice(*this);
	return (temp);
}

void Ice::use(ICharacter& target)
{
	log.print(INFO, "* shoots an ice bolt at " +  target.getName() + " *");
}