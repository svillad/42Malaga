/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:35 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

# include "Animal.hpp"
# include <iostream>
# include <string>

class Dog : virtual public Animal {
public:
	Dog();
	Dog(const Dog &c);
	Dog& operator=(const Dog &c);
	virtual ~Dog();

	virtual void makeSound(void) const;
};

#endif
