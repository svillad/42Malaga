#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <string>
#include <cmath>

class Fixed {
private:
	int					raw_bits;
	static const int	bits;

public:
	Fixed();
	Fixed(const Fixed &f);
	Fixed(int integer);
	Fixed(float floating_point);
	Fixed& operator=(const Fixed &f);
	~Fixed();

	int		getRawBits(void) const;
	void	setRawBits(int raw_bits);
	int		toInt(void) const;
	float	toFloat(void) const;

	bool	operator>(const Fixed &f) const;
	bool	operator<(const Fixed &f) const;
	bool	operator>=(const Fixed &f) const;
	bool	operator<=(const Fixed &f) const;
	bool	operator==(const Fixed &f) const;
	bool	operator!=(const Fixed &f) const;

	Fixed	operator+(const Fixed &f) const;
	Fixed	operator-(const Fixed &f) const;
	Fixed	operator*(const Fixed &f) const;
	Fixed	operator/(const Fixed &f) const;

	Fixed&	operator++(void);
	Fixed	operator++(int);
	Fixed&	operator--(void);
	Fixed	operator--(int);

	static Fixed& min(Fixed &a, Fixed &b);
	static const Fixed& min(const Fixed &a, const Fixed &b);
	static Fixed& max(Fixed &a, Fixed &b);
	static const Fixed& max(const Fixed &a, const Fixed &b);
};

std::ostream& operator<<(std::ostream &stream, const Fixed &f);

#endif
