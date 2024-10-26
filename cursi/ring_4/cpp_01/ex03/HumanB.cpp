#include "HumanB.hpp"

HumanB::HumanB() : name("none"), weapon() {}

HumanB::HumanB(const HumanB &h) : name(h.name), weapon(h.weapon) {}

HumanB&	HumanB::operator=(const HumanB &h) {
	if (this != &h) {
		name = h.name;
		weapon = h.weapon;
	}
	return (*this);
}

HumanB::HumanB(const std::string &name)
	: name(name), weapon() {}

HumanB::~HumanB() {}


void	HumanB::setWeapon(Weapon &weapon) {
	this->weapon = &weapon;
}

void HumanB::attack() const {
	if (weapon) {
		std::cout << name << " attacks with their " << weapon->getType() << std::endl;
	} else {
		std::cout << name << " has no weapon." << std::endl;
	}
}
