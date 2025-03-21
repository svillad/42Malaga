/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:09 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/25 19:04:18 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() {
  std::cout << "\e[31m[Brain]\e[0m Default constructor called for Brain" << std::endl;
  count = 0;
}

Brain::Brain(const Brain &b) {
  std::cout << "\e[31m[Brain]\e[0m Copy constructor called for Brain" << std::endl;
  *this = b;
}

Brain &Brain::operator=(const Brain &b) {
  std::cout << "\e[31m[Brain]\e[0m Copy assignment operator called for Brain" << std::endl;
  if (this != &b) {
    for (int i = 0; i < LIM; ++i) {
      ideas[i] = b.ideas[i];
    }
    count = b.count;
  }
  return (*this);
}

Brain::~Brain() {
  std::cout << "\e[31m[Brain]\e[0m Destructor called for Brain" << std::endl;
}

void Brain::print(int lim) const {
  if (lim > LIM)
    lim = LIM;
  for (int i = 0; i < lim; ++i) {
	  std::cout 	<< i + 1 << ": " << ideas[i] << std::endl;
  }
}

void Brain::setIdea(std::string idea) {
  ideas[count] = idea;
  count++;
  if (count >= LIM)
    count = 0;
}
