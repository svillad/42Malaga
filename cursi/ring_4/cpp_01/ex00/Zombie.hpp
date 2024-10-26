#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie {
private:
	std::string	name;

public:
	Zombie();
	Zombie(const Zombie &z);
	Zombie(std::string name);
	Zombie& operator=(const Zombie &z);
	~Zombie();

	void announce() const;
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif
