/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:39 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:40 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
private:
	std::string	type;

public:
	Weapon();
	Weapon(const std::string &type);
	Weapon(const Weapon &w);
	Weapon&	operator=(const Weapon &w);
	~Weapon();

	const std::string&	getType() const;
	void				setType(const std::string &newType);
};

#endif
