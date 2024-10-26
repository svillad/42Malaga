#include "Zombie.hpp"

Zombie::Zombie() : name("null") {}

Zombie::Zombie(const Zombie &z) : name(z.name) {}

Zombie::Zombie(std::string name) : name(name) {}

Zombie& Zombie::operator=(const Zombie &z) {
    if (this != &z) {
        name = z.name;
    }
    return (*this);
}

Zombie::~Zombie() {
    std::cout << name << " has been destroyed." << std::endl;
}

void    Zombie::announce() const {
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie* newZombie(std::string name) {
    return (new Zombie(name));
}

void    randomChump(std::string name) {
    Zombie stackZombie(name);
    stackZombie.announce();
}
