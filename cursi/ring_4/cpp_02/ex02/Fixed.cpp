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
	return (raw_bits >> Fixed::bits);
}

float    Fixed::toFloat(void) const {
	return ((float)raw_bits / (float)(1 << Fixed::bits));
}

bool	Fixed::operator>(const Fixed &f) const {
	return (raw_bits > f.raw_bits);
}

bool	Fixed::operator<(const Fixed &f) const {
	return (raw_bits < f.raw_bits);
}

bool	Fixed::operator>=(const Fixed &f) const {
	return (raw_bits >= f.raw_bits);
}

bool	Fixed::operator<=(const Fixed &f) const {
	return (raw_bits <= f.raw_bits);
}

bool	Fixed::operator==(const Fixed &f) const {
	return (raw_bits == f.raw_bits);
}

bool	Fixed::operator!=(const Fixed &f) const {
	return (raw_bits != f.raw_bits);
}

Fixed Fixed::operator+(const Fixed &f) const {
	return (Fixed(toFloat() + f.toFloat()));
}

Fixed Fixed::operator-(const Fixed &f) const {
	return (Fixed(toFloat() - f.toFloat()));
}

Fixed Fixed::operator*(const Fixed &f) const {
	return (Fixed(toFloat() * f.toFloat()));
}

Fixed Fixed::operator/(const Fixed &f) const {
	return (Fixed(toFloat() / f.toFloat()));
}

Fixed& Fixed::operator++() {
	raw_bits++;
	return (*this);
}

Fixed Fixed::operator++(int) {
	Fixed temp(*this);
	raw_bits++;
	return (temp);
}

Fixed& Fixed::operator--() {
	raw_bits--;
	return (*this);
}

Fixed Fixed::operator--(int) {
	Fixed temp(*this);
	raw_bits--;
	return (temp);
}

Fixed& Fixed::min(Fixed &a, Fixed &b) {
	if (a.raw_bits < b.raw_bits)
		return (a);
	else
		return (b);
}

const Fixed& Fixed::min(const Fixed &a, const Fixed &b) {
	if (a.raw_bits < b.raw_bits)
		return (a);
	else
		return (b);
}

Fixed& Fixed::max(Fixed &a, Fixed &b) {
	if (a.raw_bits > b.raw_bits)
		return (a);
	else
		return (b);
}

const Fixed& Fixed::max(const Fixed &a, const Fixed &b) {
	if (a.raw_bits > b.raw_bits)
		return (a);
	else
		return (b);
}

std::ostream& operator<<(std::ostream &stream, const Fixed &f) {
	stream << f.toFloat();
	return ((stream));
}
