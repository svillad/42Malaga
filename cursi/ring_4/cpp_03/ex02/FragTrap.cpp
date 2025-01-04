/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:24 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/04 19:34:51 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	std::cout << "\e[33m[FragTrap]\e[0m Default constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

FragTrap::FragTrap(std::string name) :  ClapTrap(name) {
	std::cout << "\e[33m[FragTrap]\e[0m Overload constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

FragTrap::FragTrap(const FragTrap &f) : ClapTrap(f) {
	std::cout << "\e[33m[FragTrap]\e[0m Copy constructor called for \e[3m" << f.name << "\e[0m" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &f) {
	std::cout << "\e[33m[FragTrap]\e[0m Copy assignment operator called for \e[3m" << f.name << "\e[0m" << std::endl;
	if (this != &f) {
		name          = f.name;
		hit_points    = f.hit_points;
		energy_points = f.energy_points;
		attack_points = f.attack_points;
	}
	return (*this);
}

FragTrap::~FragTrap() {
	std::cout << "\e[33m[FragTrap]\e[0m Destructor called for \e[3m" << name << "\e[0m" << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "\e[33m[FragTrap]\e[0m FragTrap \e[3m" << name << "\e[0m wants to High Five!!!"  << std::endl;
}

