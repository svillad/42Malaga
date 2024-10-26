#ifndef FIXED_HPP
#define FIXED_HPP

# include <iostream>
# include <string>

class Fixed {
private:
	int					raw_bits;
	static const int	bits;

public:
	Fixed();
	Fixed(const Fixed &f);
	Fixed& operator=(const Fixed &f);
	~Fixed();

	int		getRawBits(void) const;
	void	setRawBits(int raw_bits);
};

#endif
