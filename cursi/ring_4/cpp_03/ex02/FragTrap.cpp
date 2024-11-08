/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:24 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:26:24 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "\e[33m[FragTrap]\e[0m Default constructor called for " << name << std::endl;
}

FragTrap::FragTrap(std::string name) :  ClapTrap(name) {
	std::cout << "\e[33m[FragTrap]\e[0m Overload constructor called for " << name << std::endl;
}

FragTrap::FragTrap(const FragTrap &s) : ClapTrap(s) {
	std::cout << "\e[33m[FragTrap]\e[0m Copy constructor called for " << s.name << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &s) {
	std::cout << "\e[33m[FragTrap]\e[0m Copy assignment operator called for " << s.name << std::endl;
	if (this != &s) {
		name          = s.name;
		hit_points    = s.hit_points;
		energy_points = s.energy_points;
		attack_points = s.attack_points;
	}
	return (*this);
}

FragTrap::~FragTrap() {
	std::cout << "\e[33m[FragTrap]\e[0m Destructor called for " << name << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "\e[33m[FragTrap]\e[0m FragTrap "<< name << " wants to High Five!!!"  << std::endl;
}

