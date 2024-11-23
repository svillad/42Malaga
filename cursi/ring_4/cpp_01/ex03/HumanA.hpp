/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:23 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/23 18:30:05 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include <string>
#include "Weapon.hpp"

class HumanA {
private:
	std::string	name;
	Weapon		*weapon;

public:
	HumanA(const HumanA &h);
	HumanA(const std::string &name, Weapon &weapon);
	HumanA&	operator=(const HumanA &h);
	~HumanA();

	void attack() const;
};

#endif
