#include "Dog.hpp"

Dog::Dog() : AAnimal("Dog") {
	std::cout << "\e[33m[Dog]\e[0m Default constructor called for " << type << std::endl;
	brain = new Brain();
}

Dog::Dog(const Dog &d) : AAnimal(d) {
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
	brain->setIdeas("I wanna play");
}