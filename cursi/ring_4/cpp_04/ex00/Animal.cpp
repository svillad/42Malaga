/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:20 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:21 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Generic") {
  std::cout << "\e[34m[Animal]\e[0m Default constructor called for " << type << std::endl;
}

Animal::Animal(std::string type) : type(type) {
  std::cout << "\e[34m[Animal]\e[0m Overload constructor called for " << type << std::endl;
}

Animal::Animal(const Animal &a) {
  std::cout << "\e[34m[Animal]\e[0m Copy constructor called for " << type << std::endl;
  *this = a;
}

Animal &Animal::operator=(const Animal &a) {
  std::cout << "\e[34m[Animal]\e[0m Copy assignment operator called for " << a.type << std::endl;
  if (this != &a) {
    type          = a.type;
  }
  return (*this);
}

Animal::~Animal() {
  std::cout << "\e[34m[Animal]\e[0m Destructor called for " << type << std::endl;
}

void Animal::makeSound(void) const {
  std::cout << "\e[34m[Animal]\e[0m Making sound: ..." << std::endl;
}

std::string Animal::getType(void) const {
  return (type);
}

void Animal::print(void) const {
	std::cout 	<< "- type: " << type << std::endl;
}
