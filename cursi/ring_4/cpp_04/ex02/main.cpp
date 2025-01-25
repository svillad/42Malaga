/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:29:25 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/25 19:18:36 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

#define ANIMALS_COUNT 10
#define NUM_IDEAS 3

void test_simple_test() {
	std::cout << "\n********* Test: Simple test *********" << std::endl;
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();
	delete j;
	delete i;
}

void test_constructor() {
	std::cout << "\n********* Test: Constructors *********" << std::endl;
	AAnimal* animals[ANIMALS_COUNT];

    for (int i = 0; i < ANIMALS_COUNT; ++i) {
        if (i < ANIMALS_COUNT / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    for (int i = 0; i < ANIMALS_COUNT; ++i) {
        animals[i]->makeSound();
        if (Cat* cat = dynamic_cast<Cat*>(animals[i])) {
            cat->setIdeas();
            cat->printIdeas(NUM_IDEAS);
        } else if (Dog* dog = dynamic_cast<Dog*>(animals[i])) {
            dog->setIdeas();
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
    srand(time(0));
    test_simple_test();
	test_constructor();
	test_deep_copy();

    return (0);
}
