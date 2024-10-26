#include "Zombie.hpp"

int main(void) {
	Zombie		*horde = NULL;
	int			N = 5;
	std::string	name = "Zombie";

	horde = zombieHorde(N, name);
	for (int i = 0; i < N; ++i) {
		horde[i].announce();
	}
	delete[] horde;
	return (0);
}
