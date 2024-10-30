#include "ClapTrap.hpp"

void test_default_constructor() {
	std::cout << "\n********* Test: Default Constructor *********" << std::endl;
	ClapTrap clap;
	clap.print();
}

void test_overload_constructor() {
	std::cout << "\n********* Test: Overload Constructor *********" << std::endl;
	ClapTrap clap("Hero");
	clap.print();
}

void test_copy_constructor() {
	std::cout << "\n********* Test: Copy Constructor *********" << std::endl;
	ClapTrap clap1("Hero1");
	ClapTrap clap2(clap1);
	clap1.print();
	clap2.print();
}

void test_attack() {
	std::cout << "\n********* Test: Attack *********" << std::endl;
	ClapTrap clap("Attacker");
	for (int i = 0; i < DEFAULT + 1; i++) {
		clap.attack("Target");
	}
}

void test_take_damage() {
	std::cout << "\n********* Test: Take Damage *********" << std::endl;
	ClapTrap clap("Damaged");
	clap.takeDamage(5);
	clap.takeDamage(6);
	clap.takeDamage(7);
}

void test_be_repaired() {
	std::cout << "\n********* Test: Be Repaired *********" << std::endl;
	ClapTrap clap("Repairer");
	for (int i = 0; i < DEFAULT + 1; i++) {
		clap.beRepaired(2);
	}
}

void test_exceed_energy() {
	std::cout << "\n********* Test: Exceed Energy Limit *********" << std::endl;
	ClapTrap clap("Exhausted");
	for (int i = 0; i < DEFAULT + 1; i++) {
		clap.attack("Target");
	}
	clap.beRepaired(5);
}

void test_death_state() {
	std::cout << "\n********* Test: Death State *********" << std::endl;
	ClapTrap clap("Enemy");
	clap.takeDamage(10);
	clap.attack("Target");
	clap.beRepaired(5);
}

int main() {
	test_default_constructor();
	test_overload_constructor();
	test_copy_constructor();
	test_take_damage();
	test_be_repaired();
	test_exceed_energy();
	test_death_state();

	return (0);
}
