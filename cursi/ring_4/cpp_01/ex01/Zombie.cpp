/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:04 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:06 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie() : name("null") {
	std::cout << name << " has been created." << std::endl;
}

Zombie::Zombie(const Zombie &z) : name(z.name) {
	std::cout << name << " has been created." << std::endl;
}

Zombie::Zombie(std::string name) : name(name) {
	std::cout << name << " has been created." << std::endl;
}

Zombie&	Zombie::operator=(const Zombie &z) {
	if (this != &z) {
		name = z.name;
	}
	return (*this);
}

Zombie::~Zombie() {
	std::cout << name << " has been destroyed." << std::endl;
}

void	Zombie::announce() const {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie*	newZombie(std::string name) {
	return (new Zombie(name));
}

void	randomChump(std::string name) {
	Zombie stackZombie(name);
	stackZombie.announce();
}

Zombie*	zombieHorde(int N, std::string name) {
	Zombie* horde = new Zombie[N];
	for (int i = 0; i < N; ++i) {
		horde[i] = Zombie(name);
	}
	return (horde);
}
