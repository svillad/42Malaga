/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:28:30 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/25 19:14:32 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
	std::cout << "\e[32m[Cat]\e[0m Default constructor called for " << type << std::endl;
	brain = new Brain();
}

Cat::Cat(const Cat &c) : Animal(c), brain(NULL) {
	std::cout << "\e[32m[Cat]\e[0m Copy constructor called for " << c.type << std::endl;
	*this = c;
}

Cat &Cat::operator=(const Cat &c) {
	std::cout << "\e[32m[Cat]\e[0m Copy assignment operator called for " << c.type << std::endl;
	if (this != &c) {
		type = c.type;
		if (this->brain)
			delete this->brain;
		if (c.brain)
			this->brain = new Brain(*c.brain);
		else
			this->brain = NULL;
	}
	return (*this);
}

Cat::~Cat() {
	std::cout << "\e[32m[Cat]\e[0m Destructor called for " << type << std::endl;
	delete brain;
}

void Cat::makeSound(void) const {
	std::cout << "\e[32m[Cat]\e[0m Making sound: Miau!"  << std::endl;
}

void Cat::printIdeas(int lim) const {
	brain->print(lim);
}

void Cat::setIdeas(void) {
	const char* ideas[] = {
		"As the supreme being, I am hungry.",
		"I, the mighty cat, want to play.",
		"The great one feels sleepy.",
		"The almighty feline demands attention.",
		"I, ruler of all, shall go outside."
	};
  	for (int i = 0; i < LIM; ++i)
		brain->setIdea(ideas[rand() % 5]);
}
