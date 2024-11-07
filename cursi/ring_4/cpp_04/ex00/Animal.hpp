#ifndef ANIMAL_HPP
#define ANIMAL_HPP

# include <iostream>
# include <string>

class Animal {
protected:
	std::string	type;

public:
	Animal();
	Animal(std::string type);
	Animal(const Animal &a);
	Animal& operator=(const Animal &a);
	virtual ~Animal();

	virtual void makeSound(void) const;

	std::string	getType(void) const;
	void		print(void) const;
};

#endif
