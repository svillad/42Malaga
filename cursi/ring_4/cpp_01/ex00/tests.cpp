#include "Zombie.hpp"

int main(void) {
    Zombie* heapZombie = newZombie("Foo");
    heapZombie->announce();
    delete heapZombie;

    randomChump("Bar");

    return (0);
}
