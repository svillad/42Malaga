#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap("Unnamed_clap_name"), name("Unnamed") {
	std::cout << "\e[31m[DiamondTrap]\e[0m Default constructor called for " << name << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), name(name) {
	std::cout << "\e[31m[DiamondTrap]\e[0m Overload constructor called for " << name << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap &d) : ClapTrap(d) {
	std::cout << "\e[31m[DiamondTrap]\e[0m Copy constructor called for " << d.name << std::endl;
	*this = d;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &d) {
	std::cout << "\e[31m[DiamondTrap]\e[0m Copy assignment operator called for " << d.name << std::endl;
	if (this != &d) {
		name = d.name;
	}
	return (*this);
}

DiamondTrap::~DiamondTrap() {
	std::cout << "\e[31m[DiamondTrap]\e[0m Destructor called for " << name << std::endl;
}

void DiamondTrap::whoAmI(void) {
	std::cout << "\e[31m[DiamondTrap]\e[0m I'm DiamondTrap "<< name << std::endl;
	std::cout << "\e[31m[DiamondTrap]\e[0m My grandfather is ClapTrap "<< ClapTrap::name << std::endl;
}
