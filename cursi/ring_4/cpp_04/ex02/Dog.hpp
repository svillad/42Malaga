/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:23 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:23 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
#define DOG_HPP

# include "AAnimal.hpp"
# include "Brain.hpp"
# include <iostream>
# include <string>

class Dog : virtual public AAnimal {
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
