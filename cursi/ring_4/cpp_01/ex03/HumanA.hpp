#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanA {
private:
	std::string	name;
	Weapon		*weapon;

public:
	HumanA();
	HumanA(const HumanA &h);
	HumanA(const std::string &name, Weapon &weapon);
	HumanA&	operator=(const HumanA &h);
	~HumanA();

	void attack() const;
};

#endif
