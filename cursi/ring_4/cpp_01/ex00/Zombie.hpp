/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:21:54 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:21:55 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

# include <iostream>
# include <string>

class Zombie {
private:
	std::string	name;

public:
	Zombie();
	Zombie(const Zombie &z);
	Zombie(std::string name);
	Zombie& operator=(const Zombie &z);
	~Zombie();

	void announce() const;
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif