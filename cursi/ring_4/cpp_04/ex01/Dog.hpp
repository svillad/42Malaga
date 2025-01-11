/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:28:38 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/11 18:42:08 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <iostream>
# include <cstdlib>
# include <string>

class Dog : virtual public Animal {
private:
	Brain* brain;

public:
	Dog();
	Dog(const Dog &c);
	Dog& operator=(const Dog &c);
	virtual ~Dog();

	virtual void makeSound(void) const;
	virtual void printIdeas(int lim) const;
	virtual void setIdeas(void);
};

#endif
