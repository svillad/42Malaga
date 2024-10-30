#include "DiamondTrap.hpp"

void test_default_constructor() {
	std::cout << "\n********* Test: Default Constructor *********" << std::endl;
	DiamondTrap diamond;
}

void test_overload_constructor() {
	std::cout << "\n********* Test: Overload Constructor *********" << std::endl;
	DiamondTrap diamond("Hero");
}

void test_copy_constructor() {
	std::cout << "\n********* Test: Copy Constructor *********" << std::endl;
	DiamondTrap diamond1("Hero1");
	DiamondTrap diamond2(diamond1);
	diamond1.print();
	diamond2.print();
}

void test_attack() {
	std::cout << "\n********* Test: Attack *********" << std::endl;
	DiamondTrap diamond("Attacker");
	for (int i = 0; i < 5; i++) {
		diamond.attack("Target");
	}
}

void test_take_damage() {
	std::cout << "\n********* Test: Take Damage *********" << std::endl;
	DiamondTrap diamond("Damaged");
	diamond.takeDamage(50);
	diamond.takeDamage(60);
	diamond.takeDamage(70);
}

void test_be_repaired() {
	std::cout << "\n********* Test: Be Repaired *********" << std::endl;
	DiamondTrap diamond("Repairer");
	for (int i = 0; i < 5; i++) {
		diamond.beRepaired(2);
	}
}

void test_death_state() {
	std::cout << "\n********* Test: Death State *********" << std::endl;
	DiamondTrap diamond("Enemy");
	diamond.takeDamage(100);
	diamond.attack("Target");
	diamond.beRepaired(5);
}

void test_gate_keeper_mode() {
	std::cout << "\n********* Test: Gate keeper mode *********" << std::endl;
	DiamondTrap diamond("Guard");
	diamond.guardGate();
}

void test_high_five() {
	std::cout << "\n********* Test: High five *********" << std::endl;
	DiamondTrap diamond("HighFive");
	diamond.highFivesGuys();
}

void test_who_am_i() {
	std::cout << "\n********* Test: Who am I *********" << std::endl;
	DiamondTrap diamond("Hero");
	diamond.whoAmI();
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
	test_high_five();
	test_who_am_i();

	return (0);
}
