#include "Fixed.hpp"
	
const int	Fixed::bits = 8;

Fixed::Fixed() : raw_bits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &f) {
	std::cout << "Copy constructor called" << std::endl;
	*this = f;
}

Fixed::Fixed(int integer) : raw_bits(integer) {
	std::cout << "Int constructor called" << std::endl;
	raw_bits = (integer << Fixed::bits);
}

Fixed::Fixed(float floating_point) : raw_bits(floating_point) {
	std::cout << "Float constructor called" << std::endl;
	raw_bits = std::roundf(floating_point * (1 << Fixed::bits));
}

Fixed& Fixed::operator=(const Fixed &f) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &f) {
		raw_bits = f.raw_bits;
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

int    Fixed::toInt(void) const {
	return (this->raw_bits >> Fixed::bits);
}

float    Fixed::toFloat(void) const {
	return ((float)this->raw_bits / (float)(1 << Fixed::bits));
}

std::ostream&	operator<<(std::ostream &stream, Fixed const &f)
{
	stream << f.toFloat();
	return (stream);
}
