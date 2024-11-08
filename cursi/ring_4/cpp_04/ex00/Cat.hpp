/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:28 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:29 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
#define CAT_HPP

# include "Animal.hpp"
# include <iostream>
# include <string>

class Cat : virtual public Animal {
public:
	Cat();
	Cat(const Cat &c);
	Cat& operator=(const Cat &c);
	virtual ~Cat();

	virtual void makeSound(void) const;
};

#endif
