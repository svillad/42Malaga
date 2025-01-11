/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:28:27 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/11 19:48:29 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

# include <iostream>
# include <sstream>
# include <string>

# define LIM 5

class Brain {
protected:
	std::string	ideas[LIM];
	int count;

public:
	Brain();
	Brain(const Brain &a);
	Brain& operator=(const Brain &a);
	virtual ~Brain();

	void print(int lim) const;
	void setIdea(std::string idea);
};

#endif
