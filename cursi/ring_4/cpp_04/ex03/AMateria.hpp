#ifndef AMATERIA_HPP
#define AMATERIA_HPP

# include "Logger.hpp"
# include <iostream>
# include <string>

class ICharacter;

class AMateria {
protected:
    std::string type;
	Logger log;

public:
    AMateria();
    AMateria(std::string const &type);
    AMateria(AMateria const &other);
    AMateria& operator=(AMateria const &m);
    virtual ~AMateria();

    std::string const & getType() const;
    virtual AMateria* clone() const = 0;
    virtual void use(ICharacter& target);
};

#endif
