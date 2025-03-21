/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:37 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/04 19:33:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : name("Unnamed"), hit_points(DEFAULT_HIT), energy_points(DEFAULT_ENERGY),
      attack_points(DEFAULT_DAMAGE) {
  std::cout << "\e[34m[ClapTrap]\e[0m Default constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
    : name(name), hit_points(DEFAULT_HIT), energy_points(DEFAULT_ENERGY),
      attack_points(DEFAULT_DAMAGE) {
  std::cout << "\e[34m[ClapTrap]\e[0m Overload constructor called for \e[3m" << name << "\e[0m" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &c) {
  std::cout << "\e[34m[ClapTrap]\e[0m Copy constructor called for e[3m" << c.name << "\e[0m" << std::endl;
  *this = c;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &c) {
  std::cout << "\e[34m[ClapTrap]\e[0m Copy assignment operator called for e[3m" << c.name << "\e[0m" << std::endl;
  if (this != &c) {
    name          = c.name;
    hit_points    = c.hit_points;
    energy_points = c.energy_points;
    attack_points = c.attack_points;
  }
  return (*this);
}

ClapTrap::~ClapTrap() {
  std::cout << "\e[34m[ClapTrap]\e[0m Destructor called for \e[3m" << name << "\e[0m" << std::endl;
}

std::string ClapTrap::getName(void) const { return (name); }

void ClapTrap::attack(const std::string &target) {
  if (hit_points <= 0 || energy_points <= 0) {
    std::cout << "\e[34m[ClapTrap]\e[0m ClapTrap \e[3m" << name << "\e[0m"
              << " has no energy or hit points left to attack!" << std::endl;
    return;
  }
  energy_points--;
  std::cout << "\e[34m[ClapTrap]\e[0m ClapTrap \e[3m" << name << "\e[0m attacks \e[3m" << target << "\e[0m, causing "
            << attack_points << " points of damage! "
            << "Energy now: " << energy_points << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
  if (hit_points <= 0) {
    std::cout << "\e[34m[ClapTrap]\e[0m ClapTrap \e[3m" << name << "\e[0m"
              << " is already down and cannot take more damage!" << std::endl;
    return;
  }
  hit_points -= amount;
  if (hit_points < 0)
    hit_points = 0;
  std::cout << "\e[34m[ClapTrap]\e[0m ClapTrap \e[3m" << name << "\e[0m" << " takes " << amount
            << " points of damage! Hit points now: " << hit_points << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
  if (hit_points <= 0 || energy_points <= 0) {
    std::cout << "\e[34m[ClapTrap]\e[0m ClapTrap \e[3m" << name << "\e[0m"
              << " has no energy or hit points left to repair!" << std::endl;
    return;
  }
  hit_points += amount;
  energy_points--;
  std::cout << "\e[34m[ClapTrap]\e[0m ClapTrap \e[3m" << name << "\e[0m" << " repairs itself for " << amount
            << " hit points! Hit points now: " << hit_points
            << ", Energy now: " << energy_points << std::endl;
}

void ClapTrap::print(void) const {
	std::cout 	<< "- name: " << name
				<< ", hit_points: " << hit_points
				<< ", energy_points: " << energy_points
				<< ", attack_points: " << attack_points << std::endl;
}
