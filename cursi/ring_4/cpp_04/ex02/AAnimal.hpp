/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AAnimal.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:07 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:07 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AANIMAL_HPP
#define AANIMAL_HPP

# include <iostream>
# include <string>

class AAnimal {
protected:
	std::string	type;

public:
	AAnimal();
	AAnimal(std::string type);
	AAnimal(const AAnimal &a);
	AAnimal& operator=(const AAnimal &a);
	virtual ~AAnimal();

	virtual void makeSound(void) const = 0;

	std::string	getType(void) const;
	void		print(void) const;
};

#endif
