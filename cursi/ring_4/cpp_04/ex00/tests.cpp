/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:37 by svilla-d          #+#    #+#             */
/*   Updated: 2025/01/11 16:38:07 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

void test_default_constructor() {
	std::cout << "\n********* Test: Default Constructor *********" << std::endl;
	Animal animal;
	Cat cat;
	Dog dog;
}

void test_overload_constructor() {
	std::cout << "\n********* Test: Overload Constructor *********" << std::endl;
	Animal animal("Unknown");
}

void test_copy_constructor() {
	std::cout << "\n********* Test: Copy Constructor *********" << std::endl;
	Animal animal1("Hourse");
	Animal animal2(animal1);
	animal1.print();
	animal2.print();
	Cat cat1;
	Cat cat2(cat1);
	cat1.print();
	cat2.print();
	Dog dog1;
	Dog dog2(dog1);
	dog1.print();
	dog2.print();
}

void test_good_polymorphism() {
	std::cout << "\n********* Test: Good Polymorphism *********" << std::endl;
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;
}

void test_wrong_polymorphism() {
	std::cout << "\n********* Test: Wrong Polymorphism *********" << std::endl;
	const WrongAnimal* meta = new WrongAnimal();
	const WrongAnimal* i = new WrongCat();
	std::cout << i->getType() << " " << std::endl;
	i->makeSound();
	meta->makeSound();

	delete meta;
	delete i;
}

int main() {
	test_default_constructor();
	test_overload_constructor();
	test_copy_constructor();
	test_good_polymorphism();
	test_wrong_polymorphism();

	return (0);
}
