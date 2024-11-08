/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:24:34 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:24:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
	
const int	Fixed::bits = 8;

Fixed::Fixed() : raw_bits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &f) {
	std::cout << "Copy constructor called" << std::endl;
	*this = f;
}

Fixed& Fixed::operator=(const Fixed &f) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &f) {
		raw_bits = f.getRawBits();
	}
	return (*this);
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int    Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return (raw_bits);
}

void    Fixed::setRawBits(int raw_bits) {
	std::cout << "setRawBits member function called" << std::endl;
	this->raw_bits = raw_bits;
}
