#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : name("Unnamed"), hit_points(DEFAULT), energy_points(DEFAULT),
      attack_points(0) {
	std::cout << "Default constructor called for " << name << std::endl;
}

ClapTrap::ClapTrap(std::string name)
    : name(name), hit_points(DEFAULT), energy_points(DEFAULT),
      attack_points(0) {
	std::cout << "Overload constructor called for " << name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &c) {
	std::cout << "Copy constructor called for " << c.name << std::endl;
	*this = c;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &c) {
	std::cout << "Copy assignment operator called for " << c.name << std::endl;
	if (this != &c) {
		name = c.name;
		hit_points = c.hit_points;
		energy_points = c.energy_points;
		attack_points = c.attack_points;
	}
	return (*this);
}

ClapTrap::~ClapTrap() {
	std::cout << "Destructor called for " << name << std::endl;
}

std::string ClapTrap::getName(void) const {
	return (name);
}

void ClapTrap::attack(const std::string &target) {
	if (hit_points <= 0 || energy_points <= 0) {
	std::cout	<< "ClapTrap " << name
				<< " has no energy or hit points left to attack!" << std::endl;
	return;
	}
	std::cout	<< "ClapTrap " << name << " attacks " << target << ", causing "
				<< attack_points << " points of damage!" << std::endl;
	energy_points--;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (hit_points <= 0) {
	std::cout	<< "ClapTrap " << name
				<< " is already down and cannot take more damage!" << std::endl;
	return;
	}
	hit_points -= amount;
	if (hit_points < 0)
	hit_points = 0;
	std::cout	<< "ClapTrap " << name << " takes " << amount
				<< " points of damage! Hit points now: " << hit_points << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (hit_points <= 0 || energy_points <= 0) {
	std::cout	<< "ClapTrap " << name
				<< " has no energy or hit points left to repair!" << std::endl;
	return;
	}
	hit_points += amount;
	energy_points--;
	std::cout	<< "ClapTrap " << name << " repairs itself for " << amount
				<< " hit points! Hit points now: " << hit_points
				<< ", Energy now: " << energy_points << std::endl;
}

void ClapTrap::print(void) const {
	std::cout 	<< "- name: " << name
				<< ", hit_points: " << hit_points
				<< ", energy_points: " << energy_points
				<< ", attack_points: " << attack_points << std::endl;
}
