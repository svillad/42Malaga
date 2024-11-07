#include "AMateria.hpp"

AMateria::AMateria() : type("undefined") {
  log.print(DEBUG, "\e[36m[AMateria]\e[0m Default constructor called for " + type);
}

AMateria:: AMateria(std::string const &type) : type(type) {
  log.print(DEBUG, "\e[36m[AMateria]\e[0m Overload constructor called for " + type);
}

AMateria::AMateria(const AMateria &m) {
  log.print(DEBUG, "\e[36m[AMateria]\e[0m Copy constructor called for " + m.type);
  if (this != &m) {
    type = m.type;
  }
}

 AMateria& AMateria::operator=(AMateria const &m) {
  log.print(DEBUG, "\e[36m[AMateria]\e[0m Copy assignment operator called for " + m.type);
  if (this != &m) {
    type = m.type;
  }
  return (*this);
}

AMateria::~AMateria() {
  log.print(DEBUG, "\e[36m[AMateria]\e[0m Destructor called for " + type);
}

std::string const & AMateria::getType(void) const {
  return (type);
}

void AMateria::use(ICharacter& target)
{
	(void)target;
}
