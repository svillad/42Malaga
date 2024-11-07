#ifndef DOG_HPP
#define DOG_HPP

# include "Animal.hpp"
# include <iostream>
# include <string>

class Dog : virtual public Animal {
public:
	Dog();
	Dog(const Dog &c);
	Dog& operator=(const Dog &c);
	virtual ~Dog();

	virtual void makeSound(void) const;
};

#endif
