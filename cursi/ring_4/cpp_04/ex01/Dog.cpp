/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:28:36 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/11 20:04:24 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal("Dog") {
	std::cout << "\e[33m[Dog]\e[0m Default constructor called for " << type << std::endl;
	brain = new Brain();
}

Dog::Dog(const Dog &d) : Animal(d) {
	std::cout << "\e[33m[Dog]\e[0m Copy constructor called for " << d.type << std::endl;
	*this = d;
}

Dog &Dog::operator=(const Dog &d) {
	std::cout << "\e[33m[Dog]\e[0m Copy assignment operator called for " << d.type << std::endl;
	if (this != &d) {
		type = d.type;
		if (brain)
			delete brain;
		brain = new Brain(*d.brain);
	}
	return (*this);
}

Dog::~Dog() {
	std::cout << "\e[33m[Dog]\e[0m Destructor called for " << type << std::endl;
	delete brain;
}

void Dog::makeSound(void) const {
	std::cout << "\e[33m[Dog]\e[0m Making sound: Guau!"  << std::endl;
}

void Dog::printIdeas(int lim) const {
	brain->print(lim);
}

void Dog::setIdeas(void) {
	const char* ideas[] = {
        "I am so excited! I need a snack!",
        "Oh boy, I want to play! Can we go outside?",
        "I love you! I just want to cuddle.",
        "I'm so tired, but I'll guard you while I sleep.",
        "Let's go outside, I have to chase something!"
    };
  	for (int i = 0; i < LIM; ++i)
    	brain->setIdea(ideas[rand() % 5]);
}