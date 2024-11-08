/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:12 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:29:12 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
#define BRAIN_HPP

# include <iostream>
# include <string>

# define LIM 100

class Brain {
protected:
	std::string	ideas[LIM];

public:
	Brain();
	Brain(const Brain &a);
	Brain& operator=(const Brain &a);
	virtual ~Brain();

	void print(int lim) const;
	void setIdeas(std::string idea);
};

#endif
