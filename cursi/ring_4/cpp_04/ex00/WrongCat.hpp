#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

# include "WrongAnimal.hpp"
# include <iostream>
# include <string>

class WrongCat : virtual public WrongAnimal {
public:
	WrongCat();
	WrongCat(const WrongCat &c);
	WrongCat& operator=(const WrongCat &c);
	virtual ~WrongCat();

	virtual void makeSound(void) const;
};

#endif
