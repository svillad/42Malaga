/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:49 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:50 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("WrongCat") {
	std::cout << "\e[32m[WrongCat]\e[0m Default constructor called for " << type << std::endl;
}

WrongCat::WrongCat(const WrongCat &c) : WrongAnimal(c) {
	std::cout << "\e[32m[WrongCat]\e[0m Copy constructor called for " << c.type << std::endl;
}

WrongCat &WrongCat::operator=(const WrongCat &c) {
	std::cout << "\e[32m[WrongCat]\e[0m Copy assignment operator called for " << c.type << std::endl;
	if (this != &c) {
		type = c.type;
	}
	return (*this);
}

WrongCat::~WrongCat() {
	std::cout << "\e[32m[WrongCat]\e[0m Destructor called for " << type << std::endl;
}

void WrongCat::makeSound(void) const {
	std::cout << "\e[32m[WrongCat]\e[0m Making sound: Miau!"  << std::endl;
}

