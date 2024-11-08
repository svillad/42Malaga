/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:21 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:26:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

# include <iostream>
# include <string>

# define DEFAULT_HIT 100
# define DEFAULT_ENERGY 50
# define DEFAULT_DAMAGE 20

class ClapTrap {
protected:
	std::string	name;
	int			hit_points;
	int			energy_points;
	int			attack_points;

public:
	ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(const ClapTrap &f);
	ClapTrap& operator=(const ClapTrap &f);
	~ClapTrap();

	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);

	std::string	getName(void) const;
	void		print(void) const;
};

#endif
