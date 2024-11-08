/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:36 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AMATERIA_HPP
#define AMATERIA_HPP

# include "Logger.hpp"
# include <iostream>
# include <string>

class ICharacter;

class AMateria {
protected:
    std::string type;
	Logger log;

public:
    AMateria();
    AMateria(std::string const &type);
    AMateria(AMateria const &other);
    AMateria& operator=(AMateria const &m);
    virtual ~AMateria();

    std::string const & getType() const;
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#endif
