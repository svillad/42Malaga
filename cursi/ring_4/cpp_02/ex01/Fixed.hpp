/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:24:52 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:24:53 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	Fixed(int integer);
	Fixed(float floating_point);
	Fixed& operator=(const Fixed &f);
	~Fixed();

	int		getRawBits(void) const;
	void	setRawBits(int raw_bits);

	int		toInt(void) const;
	float	toFloat(void) const;
};

std::ostream&	operator<<(std::ostream &stream, Fixed const &f);

#endif
