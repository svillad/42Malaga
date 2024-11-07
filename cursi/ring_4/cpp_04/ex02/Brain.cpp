#include "Brain.hpp"

Brain::Brain() {
  std::cout << "\e[31m[Brain]\e[0m Default constructor called for Brain" << std::endl;
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

void Brain::setIdeas(std::string idea) {
  for (int i = 0; i < LIM; ++i) {
      ideas[i] = std::to_string(i) + "_" + idea;
  }
}

