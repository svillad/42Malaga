#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#define ANIMALS_COUNT 10
#define NUM_IDEAS 3

void test_simple_test() {
	std::cout << "\n********* Test: Simple test *********" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete j;
	delete i;
}

void test_constructor() {
	std::cout << "\n********* Test: Constructors *********" << std::endl;
	Animal* animals[ANIMALS_COUNT];

    for (int i = 0; i < ANIMALS_COUNT; ++i) {
        if (i < ANIMALS_COUNT / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < ANIMALS_COUNT; ++i) {
        animals[i]->makeSound();
        if (Cat* cat = dynamic_cast<Cat*>(animals[i])) {
            cat->printIdeas(NUM_IDEAS);
        } else if (Dog* dog = dynamic_cast<Dog*>(animals[i])) {
            dog->printIdeas(NUM_IDEAS);
        }
    }

	for (int i = 0; i < ANIMALS_COUNT; ++i) {
        delete animals[i];
    }
}

void test_deep_copy() {
	std::cout << "\n********* Test: Deep copy *********" << std::endl;
    Cat* originalCat = new Cat();
	std::cout << "Original cat ideas:" << std::endl;
	originalCat->setIdeas();
    originalCat->printIdeas(NUM_IDEAS);

    Cat* copiedCat = new Cat(*originalCat);
    delete originalCat;
	std::cout << "Copy cat ideas:" << std::endl;
    copiedCat->printIdeas(NUM_IDEAS);
    delete copiedCat;
}

int main() {
    test_simple_test();
	test_constructor();
	test_deep_copy();

    return (0);
}
