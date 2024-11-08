/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:30 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:26:30 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

void test_default_constructor() {
	std::cout << "\n********* Test: Default Constructor *********" << std::endl;
	FragTrap frag;
	frag.print();
}

void test_overload_constructor() {
	std::cout << "\n********* Test: Overload Constructor *********" << std::endl;
	FragTrap frag("Hero");
	frag.print();
}

void test_copy_constructor() {
	std::cout << "\n********* Test: Copy Constructor *********" << std::endl;
	FragTrap frag1("Hero1");
	FragTrap frag2(frag1);
	frag1.print();
	frag2.print();
}

void test_attack() {
	std::cout << "\n********* Test: Attack *********" << std::endl;
	FragTrap frag("Attacker");
	for (int i = 0; i < 5; i++) {
		frag.attack("Target");
	}
}

void test_take_damage() {
	std::cout << "\n********* Test: Take Damage *********" << std::endl;
	FragTrap frag("Damaged");
	frag.takeDamage(50);
	frag.takeDamage(60);
	frag.takeDamage(70);
}

void test_be_repaired() {
	std::cout << "\n********* Test: Be Repaired *********" << std::endl;
	FragTrap frag("Repairer");
	for (int i = 0; i < 5; i++) {
		frag.beRepaired(2);
	}
}

void test_death_state() {
	std::cout << "\n********* Test: Death State *********" << std::endl;
	FragTrap frag("Enemy");
	frag.takeDamage(100);
	frag.attack("Target");
	frag.beRepaired(5);
}

void test_high_five() {
	std::cout << "\n********* Test: High five *********" << std::endl;
	FragTrap frag("HighFive");
	frag.highFivesGuys();
}

int main() {
	test_default_constructor();
	test_overload_constructor();
	test_copy_constructor();
	test_attack();
	test_take_damage();
	test_be_repaired();
	test_death_state();
	test_high_five();

	return (0);
}
