#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongGeneric") {
  std::cout << "\e[34m[WrongAnimal]\e[0m Default constructor called for " << type << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : type(type) {
  std::cout << "\e[34m[WrongAnimal]\e[0m Overload constructor called for " << type << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &a) {
  std::cout << "\e[34m[WrongAnimal]\e[0m Copy constructor called for " << type << std::endl;
  *this = a;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &a) {
  std::cout << "\e[34m[WrongAnimal]\e[0m Copy assignment operator called for " << a.type << std::endl;
  if (this != &a) {
    type          = a.type;
  }
  return (*this);
}

WrongAnimal::~WrongAnimal() {
  std::cout << "\e[34m[WrongAnimal]\e[0m Destructor called for " << type << std::endl;
}

void WrongAnimal::makeSound(void) const {
  std::cout << "\e[34m[WrongAnimal]\e[0m Making sound: ..." << std::endl;
}

std::string WrongAnimal::getType(void) const {
  return (type);
}

void WrongAnimal::print(void) const {
	std::cout 	<< "- type: " << type << std::endl;
}
