#ifndef DOG_HPP
#define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"
# include <iostream>
# include <string>

class Dog : virtual public Animal {
private:
	Brain* brain;

public:
	Dog();
	Dog(const Dog &c);
	Dog& operator=(const Dog &c);
	virtual ~Dog();

	virtual void makeSound(void) const;
	virtual void printIdeas(int lim) const;
	virtual void setIdeas(void);
};

#endif
