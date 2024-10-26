#ifndef HUMANB_HPP
#define HUMANB_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanB {
private:
	std::string	name;
	Weapon		*weapon;

public:
	HumanB();
	HumanB(const HumanB &h);
	HumanB(const std::string &name);
	HumanB&	operator=(const HumanB &h);
	~HumanB();

	void setWeapon(Weapon& weapon);
	void attack() const;
};

#endif
