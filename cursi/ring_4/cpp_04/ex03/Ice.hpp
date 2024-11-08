/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:52 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:53 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
#define ICE_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"
# include "Logger.hpp"
# include <iostream>
# include <string>

class Ice : virtual public AMateria {
public:
	Ice();
	Ice(const Ice &c);
	Ice& operator=(const Ice &c);
	virtual ~Ice();

	virtual AMateria* clone(void) const;
	virtual void use(ICharacter& target);
};

#endif
