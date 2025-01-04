/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:59 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/11 15:31:07 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
	std::cout << "\e[32m[ScavTrap]\e[0m Default constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

ScavTrap::ScavTrap(std::string name) :  ClapTrap(name) {
	std::cout << "\e[32m[ScavTrap]\e[0m Overload constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &s) : ClapTrap(s) {
	std::cout << "\e[32m[ScavTrap]\e[0m Copy constructor called for \e[3m" << s.name << "\e[0m" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &s) {
	std::cout << "\e[32m[ScavTrap]\e[0m Copy assignment operator called for \e[3m" << s.name << "\e[0m" << std::endl;
	if (this != &s) {
		name          = s.name;
		hit_points    = s.hit_points;
		energy_points = s.energy_points;
		attack_points = s.attack_points;
	}
	return (*this);
}

ScavTrap::~ScavTrap() {
	std::cout << "\e[32m[ScavTrap]\e[0m Destructor called for \e[3m" << name << "\e[0m" << std::endl;
}

void ScavTrap::attack(const std::string &target) {
  if (hit_points <= 0 || energy_points <= 0) {
    std::cout << "\e[32m[ScavTrap]\e[0m ScavTrap \e[3m" << name << "\e[0m"
              << " has no energy or hit points left to attack!" << std::endl;
    return;
  }
  energy_points--;
  std::cout << "\e[32m[ScavTrap]\e[0m ScavTrap \e[3m" << name << "\e[0m super attacks \e[3m" << target << "\e[0m, causing "
            << attack_points << " points of damage! "
            << "Energy now: " << energy_points << std::endl;
}

void ScavTrap::guardGate(void) {
	std::cout << "\e[32m[ScavTrap]\e[0m ScavTrap \e[3m" << name << "\e[0m is now in Gate keeper mode"  << std::endl;
}

