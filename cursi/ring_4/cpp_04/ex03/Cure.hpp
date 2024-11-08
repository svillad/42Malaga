/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:47 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
#define CURE_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"
# include "Logger.hpp"
# include <iostream>
# include <string>

class Cure : virtual public AMateria {
public:
	Cure();
	Cure(const Cure &c);
	Cure& operator=(const Cure &c);
	virtual ~Cure();

	virtual AMateria* clone(void) const;
	virtual void use(ICharacter& target);
};

#endif
