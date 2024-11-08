/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:59 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:00 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << "\e[32m[ScavTrap]\e[0m Default constructor called for " << name << std::endl;
}

ScavTrap::ScavTrap(std::string name) :  ClapTrap(name) {
	std::cout << "\e[32m[ScavTrap]\e[0m Overload constructor called for " << name << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &s) : ClapTrap(s) {
	std::cout << "\e[32m[ScavTrap]\e[0m Copy constructor called for " << s.name << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &s) {
	std::cout << "\e[32m[ScavTrap]\e[0m Copy assignment operator called for " << s.name << std::endl;
	if (this != &s) {
		name          = s.name;
		hit_points    = s.hit_points;
		energy_points = s.energy_points;
		attack_points = s.attack_points;
	}
	return (*this);
}

ScavTrap::~ScavTrap() {
	std::cout << "\e[32m[ScavTrap]\e[0m Destructor called for " << name << std::endl;
}

void ScavTrap::guardGate(void) {
	std::cout << "\e[32m[ScavTrap]\e[0m ScavTrap "<< name << " is now in Gate keeper mode"  << std::endl;
}

