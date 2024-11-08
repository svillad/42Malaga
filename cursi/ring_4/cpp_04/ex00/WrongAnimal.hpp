/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:27:46 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal {
protected:
	std::string	type;

public:
	WrongAnimal();
	WrongAnimal(std::string type);
	WrongAnimal(const WrongAnimal &a);
	WrongAnimal& operator=(const WrongAnimal &a);
	virtual ~WrongAnimal();

	void makeSound(void) const;

	std::string	getType(void) const;
	void		print(void) const;
};

#endif
