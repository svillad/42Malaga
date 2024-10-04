#include <iostream>
#include <cassert>
#include "PhoneBook.hpp"

void menu(void) {
	std::cout << "This program only accepts 3 commands: ADD, SEARCH and EXIT."
			  << std::endl;
	std::cout << "• ADD: save a new contact." << std::endl;
	std::cout << "• SEARCH: display a specific contact." << std::endl;
	std::cout << "• EXIT: The program quits." << std::endl;
	std::cout << "• Any other input is discarded." << std::endl;
	std::cout << std::endl;
}

int search_contact(PhoneBook &p) {
	int index;

	if (p.get_size() <= 0) {
		std::cout << "There are no contacts to display" << std::endl;
		return (-1);
	}
	p.print();
	do {
		std::cout << "Enter the index of the contact to display: ";
		std::cin >> index;
		if (index >= p.get_size() || index < 0)
			std::cout << "Invalid index. The index must be greater than or equal"
				" to 0 and less than " << p.get_size() << std::endl;
	} while (index >= p.get_size() || index < 0);
	return (index);
}

int main() {
	PhoneBook	phonebook;
	Contact		contact;
	std::string	command;
	int			index;

	menu();
	while (true) {
		std::cout << "Enter a command (ADD, SEARCH, EXIT): ";
		std::cin >> command;

		if (command == "ADD")
			phonebook.add();
		else if (command == "SEARCH") {
			index = search_contact(phonebook);
			if (index >= 0) {
				contact = phonebook.search(index);
				contact.print_full();
			}
		} 
		else if (command == "EXIT") {
			std::cout << "Exiting the program." << std::endl;
			break;
		} 
		else
			std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT."
					  << std::endl;
		std::cout << std::endl;
	}
	return (0);
}
