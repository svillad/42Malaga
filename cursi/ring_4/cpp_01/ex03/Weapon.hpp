#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
	std::string	type;

public:
	Weapon();
	Weapon(const std::string &type);
	Weapon(const Weapon &w);
	Weapon&	operator=(const Weapon &w);
	~Weapon();

	const std::string&	getType() const;
	void				setType(const std::string &newType);
};

#endif
