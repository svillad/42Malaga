/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:26:07 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/23 20:13:21 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

void test_default_constructor() {
	std::cout << "\n********* Test: Default Constructor *********" << std::endl;
	ScavTrap scav;
	scav.print();
}

void test_overload_constructor() {
	std::cout << "\n********* Test: Overload Constructor *********" << std::endl;
	ScavTrap scav("Hero");
	scav.print();
}

void test_copy_constructor() {
	std::cout << "\n********* Test: Copy Constructor *********" << std::endl;
	ScavTrap scav1("Hero1");
	ScavTrap scav2(scav1);
	scav1.print();
	scav2.print();
}

void test_attack() {
	std::cout << "\n********* Test: Attack *********" << std::endl;
	ScavTrap scav("Attacker");
	scav.print();
	for (int i = 0; i < 5; i++) {
		scav.attack("Target");
	}
}

void test_take_damage() {
	std::cout << "\n********* Test: Take Damage *********" << std::endl;
	ScavTrap scav("Damaged");
	scav.print();
	scav.takeDamage(50);
	scav.takeDamage(60);
	scav.takeDamage(70);
}

void test_be_repaired() {
	std::cout << "\n********* Test: Be Repaired *********" << std::endl;
	ScavTrap scav("Repairer");
	scav.print();
	for (int i = 0; i < 5; i++) {
		scav.beRepaired(2);
	}
}

void test_death_state() {
	std::cout << "\n********* Test: Death State *********" << std::endl;
	ScavTrap scav("Enemy");
	scav.print();
	scav.takeDamage(100);
	scav.attack("Target");
	scav.beRepaired(5);
}

void test_gate_keeper_mode() {
	std::cout << "\n********* Test: Gate keeper mode *********" << std::endl;
	ScavTrap scav("Guard");
	scav.print();
	scav.guardGate();
}

int main() {
	test_default_constructor();
	test_overload_constructor();
	test_copy_constructor();
	test_attack();
	test_take_damage();
	test_be_repaired();
	test_death_state();
	test_gate_keeper_mode();

	return (0);
}
