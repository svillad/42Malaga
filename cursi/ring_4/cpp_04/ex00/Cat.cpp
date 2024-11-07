#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
	std::cout << "\e[32m[Cat]\e[0m Default constructor called for " << type << std::endl;
}

Cat::Cat(const Cat &c) : Animal(c) {
	std::cout << "\e[32m[Cat]\e[0m Copy constructor called for " << c.type << std::endl;
}

Cat &Cat::operator=(const Cat &c) {
	std::cout << "\e[32m[Cat]\e[0m Copy assignment operator called for " << c.type << std::endl;
	if (this != &c) {
		type = c.type;
	}
	return (*this);
}

Cat::~Cat() {
	std::cout << "\e[32m[Cat]\e[0m Destructor called for " << type << std::endl;
}

void Cat::makeSound(void) const {
	std::cout << "\e[32m[Cat]\e[0m Making sound: Miau!"  << std::endl;
}

