#include <iostream>
#include <cassert>
#include "PhoneBook.hpp"

void test_initial_contacts(void)
{
	PhoneBook phonebook;

	std::cout << "\n*********   test_initial_contacts   *********" << std::endl;

	phonebook.add(Contact("Juan Camilo", "Villa", "juank", "123456789", "I love pizza"));
	phonebook.add(Contact("Luis Felipe", "Duarte", "pipe", "987654321", "I have a pet snake"));
	phonebook.add(Contact("Sebastian", "Duran", "seba", "456789123", "I collect stamps"));
	phonebook.add(Contact("David", "Penalosa", "dakraiv", "321654987", "I am afraid of spiders"));
	phonebook.add(Contact("Sara Vanesa", "Arias", "tute", "654321789", "I once won a contest"));

	std::cout   << "Checking that the PhoneBook size is 5: "
				<< phonebook.get_size() << std::endl;
	assert(phonebook.get_size() == 5);
	phonebook.print();
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

void test_limit_contacts(void)
{
	PhoneBook phonebook;

	std::cout << "\n*********   test_limit_contacts   *********" << std::endl;
	for (int i = 0; i < LIM; ++i)
	{
		phonebook.add(
			Contact("Contact" + std::to_string(i + 1),
					"LastName" + std::to_string(i + 1),
					"Nick" + std::to_string(i + 1),
					std::to_string(101 + i),
					"Secret" + std::to_string(i + 1)));
	}

	std::cout   << "Checking that the PhoneBook size is " << LIM << ": "
				<< phonebook.get_size() << std::endl;
	assert(phonebook.get_size() == LIM);
	phonebook.print();
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

void test_overwrite_old_contacts(void)
{
	PhoneBook phonebook;

	std::cout << "\n*********   test_overwrite_old_contacts   *********" << std::endl;
	for (int i = 0; i < LIM; ++i)
	{
		phonebook.add(
			Contact("Contact" + std::to_string(i + 1),
					"LastName" + std::to_string(i + 1),
					"Nick" + std::to_string(i + 1),
					std::to_string(101 + i),
					"Secret" + std::to_string(i + 1)));
	}

	phonebook.add(
		Contact("NewCont1", "NewLN1", "NewNick1", "111", "I have no secrets"));
	phonebook.add(
		Contact("NewCont2", "NewLN2", "NewNick2", "222", "I have no secrets"));
	std::cout   << "Checking that the PhoneBook size is " << LIM << ": "
				<< phonebook.get_size() << std::endl;
	assert(phonebook.get_size() == LIM);
	phonebook.print();
	std::cout << "\033[32mOK\033[0m" << std::endl;
}


void test_search_contact(void)
{
	PhoneBook	phonebook;
	Contact		contact;

	std::cout << "\n*********   test_search_contact   *********" << std::endl;

	phonebook.add(Contact("Juan Camilo", "Villa", "juank", "123456789", "I love pizza"));
	phonebook.add(Contact("Luis Felipe", "Duarte", "pipe", "987654321", "I have a pet snake"));
	phonebook.add(Contact("Sebastian", "Duran", "svillad", "456789123", "I collect stamps"));
	phonebook.add(Contact("David", "Penalosa", "dakraiv", "321654987", "I am afraid of spiders"));
	phonebook.add(Contact("Sara Vanesa", "Arias", "tute", "654321789", "I once won a contest"));

	phonebook.print();
	std::cout << "Checking contact 2: " << std::endl;
	contact = phonebook.search(2);
	assert(contact.get_first_name() == "Sebastian");
	assert(contact.get_last_name() == "Duran");
	assert(contact.get_nickname() == "svillad");
	assert(contact.get_phone_number() == "456789123");
	assert(contact.get_darkest_secret() == "I collect stamps");
	contact.print_full();
	std::cout << "\033[32mOK\033[0m" << std::endl;
}

int main()
{
	test_initial_contacts();
	test_limit_contacts();
	test_overwrite_old_contacts();
	test_search_contact();
	std::cout << "All tests passed successfully." << std::endl;
	return (0);
}