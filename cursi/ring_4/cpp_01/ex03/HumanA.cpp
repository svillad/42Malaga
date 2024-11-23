/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:20 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/23 18:11:57 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(const HumanA &h) {
	*this = h;
}

HumanA&	HumanA::operator=(const HumanA &h) {
	if (this != &h) {
		name = h.name;
		weapon = h.weapon;
	}
	return (*this);
}

HumanA::HumanA(const std::string &name, Weapon &weapon)
	 : name(name), weapon(&weapon) {}

HumanA::~HumanA() {}


void HumanA::attack() const {
    std::cout << name << " attacks with their " << weapon->getType() << std::endl;
}
