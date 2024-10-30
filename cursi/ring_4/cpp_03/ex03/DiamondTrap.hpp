#ifndef DIAMONDTRAP_HPP
#define DIAMONDTRAP_HPP

# include "FragTrap.hpp"
# include "ScavTrap.hpp"
# include <iostream>
# include <string>

# define DEFAULT 10

class DiamondTrap : public FragTrap, public ScavTrap {
private:
	std::string	name;
	using FragTrap::hit_points;
	using ScavTrap::energy_points;
	using FragTrap::attack_points;
	
public:
	DiamondTrap();
	DiamondTrap(std::string name);
	DiamondTrap(const DiamondTrap &f);
	DiamondTrap& operator=(const DiamondTrap &f);
	~DiamondTrap();

	using ScavTrap::attack;

	void whoAmI(void);
};

#endif
