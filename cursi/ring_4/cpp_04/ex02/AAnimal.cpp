/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:03 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:04 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"

AAnimal::AAnimal() : type("Generic") {
  std::cout << "\e[34m[AAnimal]\e[0m Default constructor called for " << type << std::endl;
}

AAnimal::AAnimal(std::string type) : type(type) {
  std::cout << "\e[34m[AAnimal]\e[0m Overload constructor called for " << type << std::endl;
}

AAnimal::AAnimal(const AAnimal &a) {
  std::cout << "\e[34m[AAnimal]\e[0m Copy constructor called for " << a.type << std::endl;
  *this = a;
}

AAnimal &AAnimal::operator=(const AAnimal &a) {
  std::cout << "\e[34m[AAnimal]\e[0m Copy assignment operator called for " << a.type << std::endl;
  if (this != &a) {
    type          = a.type;
  }
  return (*this);
}

AAnimal::~AAnimal() {
  std::cout << "\e[34m[AAnimal]\e[0m Destructor called for " << type << std::endl;
}

std::string AAnimal::getType(void) const {
  return (type);
}

void AAnimal::print(void) const {
	std::cout 	<< "- type: " << type << std::endl;
}
