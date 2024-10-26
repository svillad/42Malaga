#include "HumanA.hpp"

HumanA::HumanA() : name("none"), weapon() {}

HumanA::HumanA(const HumanA &h) : name(h.name), weapon(h.weapon) {}

HumanA&	HumanA::operator=(const HumanA &h) {
	if (this != &h) {
		name = h.name;
		weapon = h.weapon;
	}
	return (*this);
}

HumanA::HumanA(const std::string &name, Weapon &weapon)
	 : name(name), weapon(&weapon) {}

HumanA::~HumanA() {}


void HumanA::attack() const {
    std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}
