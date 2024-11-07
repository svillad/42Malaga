#ifndef ICE_HPP
#define ICE_HPP

# include "AMateria.hpp"
# include "ICharacter.hpp"
# include "Logger.hpp"
# include <iostream>
# include <string>

class Ice : virtual public AMateria {
public:
	Ice();
	Ice(const Ice &c);
	Ice& operator=(const Ice &c);
	virtual ~Ice();

	virtual AMateria* clone(void) const;
	virtual void use(ICharacter& target);
};

#endif
