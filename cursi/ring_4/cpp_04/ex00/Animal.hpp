/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:23 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:24 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal {
protected:
	std::string	type;

public:
	Animal();
	Animal(std::string type);
	Animal(const Animal &a);
	Animal& operator=(const Animal &a);
	virtual ~Animal();

	virtual void makeSound(void) const;

	std::string	getType(void) const;
	void		print(void) const;
};

#endif
