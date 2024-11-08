/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:24:38 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:24:39 by svilla-d         ###   ########.fr       */
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
	Fixed& operator=(const Fixed &f);
	~Fixed();

	int		getRawBits(void) const;
	void	setRawBits(int raw_bits);
};

#endif
