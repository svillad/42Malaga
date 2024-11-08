/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:44 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"

Cure::Cure() : AMateria("cure") {
	log.print(DEBUG, "\e[33m[Cure]\e[0m Default constructor called for " + type);
}

Cure::Cure(const Cure &c) : AMateria(c) {
	log.print(DEBUG, "\e[33m[Cure]\e[0m Copy constructor called for " + c.type);
}

Cure &Cure::operator=(const Cure &c) {
	log.print(DEBUG, "\e[33m[Cure]\e[0m Copy assignment operator called for " + c.type);
	if (this != &c) {
		type = c.type;
	}
	return (*this);
}

Cure::~Cure() {
	log.print(DEBUG, "\e[33m[Cure]\e[0m Destructor called for " + type);
}

AMateria* Cure::clone() const
{
	log.print(DEBUG, "\e[33m[Cure]\e[0m Start clone process");
	AMateria *temp = new Cure(*this);
	return (temp);
}

void Cure::use(ICharacter& target)
{
	log.print(INFO, "* heals " +  target.getName() + "\'s wounds *");
}