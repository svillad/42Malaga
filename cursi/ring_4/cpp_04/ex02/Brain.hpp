/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:12 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/11 16:48:53 by svilla-d         ###   ########.fr       */
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

template<typename T>
std::string to_string(const T& value);

#endif
