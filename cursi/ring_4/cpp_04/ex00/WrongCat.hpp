/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:52 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:53 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

# include "WrongAnimal.hpp"
# include <iostream>
# include <string>

class WrongCat : virtual public WrongAnimal {
public:
	WrongCat();
	WrongCat(const WrongCat &c);
	WrongCat& operator=(const WrongCat &c);
	virtual ~WrongCat();

	virtual void makeSound(void) const;
};

#endif
