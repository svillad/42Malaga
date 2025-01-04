/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:43 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/04 19:37:57 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("Unnamed_clap_name"), name("Unnamed") {
	std::cout << "\e[31m[DiamondTrap]\e[0m Default constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), name(name) {
	std::cout << "\e[31m[DiamondTrap]\e[0m Overload constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &d) : ClapTrap(d) {
	std::cout << "\e[31m[DiamondTrap]\e[0m Copy constructor called for \e[3m" << d.name << "\e[0m" << std::endl;
	*this = d;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &d) {
	std::cout << "\e[31m[DiamondTrap]\e[0m Copy assignment operator called for \e[3m" << d.name << "\e[0m" << std::endl;
	if (this != &d) {
		name = d.name;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap() {
	std::cout << "\e[31m[DiamondTrap]\e[0m Destructor called for \e[3m" << name << "\e[0m" << std::endl;
}

void DiamondTrap::whoAmI(void) {
	std::cout << "\e[31m[DiamondTrap]\e[0m I'm DiamondTrap \e[3m" << name << "\e[0m" << std::endl;
	std::cout << "\e[31m[DiamondTrap]\e[0m My grandfather is ClapTrap \e[3m" << ClapTrap::name << "\e[0m" << std::endl;
}
