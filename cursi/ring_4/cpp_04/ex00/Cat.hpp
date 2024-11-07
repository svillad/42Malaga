#ifndef CAT_HPP
#define CAT_HPP

# include "Animal.hpp"
# include <iostream>
# include <string>

class Cat : virtual public Animal {
public:
	Cat();
	Cat(const Cat &c);
	Cat& operator=(const Cat &c);
	virtual ~Cat();

	virtual void makeSound(void) const;
};

#endif
