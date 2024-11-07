#ifndef CURE_HPP
#define CURE_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"
# include "Logger.hpp"
# include <iostream>
# include <string>

class Cure : virtual public AMateria {
public:
	Cure();
	Cure(const Cure &c);
	Cure& operator=(const Cure &c);
	virtual ~Cure();

	virtual AMateria* clone(void) const;
	virtual void use(ICharacter& target);
};

#endif
