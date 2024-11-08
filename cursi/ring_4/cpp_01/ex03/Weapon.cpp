/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:36 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon() : type("none") {}

Weapon::Weapon(const std::string& type) : type(type) {}

Weapon::Weapon(const Weapon &w) : type(w.type) {}

Weapon&	Weapon::operator=(const Weapon &w) {
	if (this != &w) {
		type = w.type;
	}
	return (*this);
}

Weapon::~Weapon() {}

const std::string& Weapon::getType() const {
	return (type);
}

void Weapon::setType(const std::string& newType) {
	type = newType;
}
