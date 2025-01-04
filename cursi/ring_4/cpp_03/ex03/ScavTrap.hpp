/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:02 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/04 19:35:58 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

# include "ClapTrap.hpp"
# include <iostream>
# include <string>

# define DEFAULT 10

class ScavTrap : virtual public ClapTrap {
public:
	ScavTrap();
	ScavTrap(std::string name);
	ScavTrap(const ScavTrap &f);
	ScavTrap& operator=(const ScavTrap &f);
	~ScavTrap();

	void attack(const std::string& target);
	void guardGate(void);
};

#endif
