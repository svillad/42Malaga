/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:31 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:32 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
	std::cout << "\e[33m[Dog]\e[0m Default constructor called for " << type << std::endl;
}

Dog::Dog(const Dog &c) : Animal(c) {
	std::cout << "\e[33m[Dog]\e[0m Copy constructor called for " << c.type << std::endl;
}

Dog &Dog::operator=(const Dog &c) {
	std::cout << "\e[33m[Dog]\e[0m Copy assignment operator called for " << c.type << std::endl;
	if (this != &c) {
		type = c.type;
	}
	return (*this);
}

Dog::~Dog() {
	std::cout << "\e[33m[Dog]\e[0m Destructor called for " << type << std::endl;
}

void Dog::makeSound(void) const {
	std::cout << "\e[33m[Dog]\e[0m Making sound: Guau!"  << std::endl;
}

