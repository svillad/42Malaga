#ifndef CHARACTER_HPP
#define CHARACTER_HPP

# include "ICharacter.hpp"
# include "AMateria.hpp"
# include "Logger.hpp"
# include <iostream>

# define SLOT_SIZE 4
# define BAG_SIZE 100

class Character : public ICharacter {
private:
    std::string name;
    AMateria*   slot[SLOT_SIZE];
    AMateria*   bag[BAG_SIZE];
    Logger      log;

    void initArray(AMateria* array[], int size);
    void freeArray(AMateria* array[], int size);
    void copyArray(AMateria* dst[], AMateria* const src[], int size);
    int exists(AMateria* m) const;

public:
    Character();
    Character(std::string const &name);
    Character(Character const &other);
    Character& operator=(Character const &other);
    virtual ~Character();

    std::string const & getName() const;
    void equip(AMateria* m);
    void unequip(int idx);
    void use(int idx, ICharacter& target);
};

#endif
