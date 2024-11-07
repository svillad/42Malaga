#include "MateriaSource.hpp"
#include "Character.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
    IMateriaSource* src = new MateriaSource();
    src->learnMateria(NULL);
    src->learnMateria(new Ice());
    src->learnMateria(new Cure());

    ICharacter* me = new Character("me");
   
    AMateria* tmp;
    tmp = src->createMateria("ice");
    src->learnMateria(tmp);
    src->learnMateria(tmp);
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);
    tmp = src->createMateria("cure");
    me->equip(tmp);

    ICharacter* bob = new Character("bob");

    me->use(0, *bob);
    me->use(1, *bob);
    me->use(2, *bob);
    me->use(3, *bob);
    me->use(4, *bob);

    me->unequip(0);
    me->unequip(1);
    me->unequip(1);
    me->unequip(2);
    me->unequip(4);

    delete bob;
    delete me;
    delete src;

    return (0);
}