/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:12:31 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/16 20:00:34 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : size(0), oldest(0) {}

PhoneBook::PhoneBook(const PhoneBook& p) 
	: size(p.size), oldest(p.oldest) {
	for (int i = 0; i < size; ++i) {
		contacts[i] = p.contacts[i];
	}
}

PhoneBook& PhoneBook::operator=(const PhoneBook& p) {
	if (this != &p) {
		size = p.size;
		oldest = p.oldest;
		for (int i = 0; i < size; ++i) {
			contacts[i] = p.contacts[i];
		}
	}
	return (*this);
}

int PhoneBook::get_size() const {
	return (size);
}


bool PhoneBook::add() {
	Contact c;
	int pos = size;

	if (size >= LIM) {
		pos = oldest;    
	}
	if (!c.create())
		return false;
	contacts[pos] = c;
	size++;

	if (size > LIM) {
		size = LIM;
		oldest = (oldest + 1) % LIM;
	}
	std::cout << "Contact added successfully!" << std::endl;
	return true;
}

void PhoneBook::add(const Contact& c) {
	int pos = size;

	if (size >= LIM) {
		pos = oldest;
	}

	contacts[pos] = c;
	size++;

	if (size > LIM) {
		size = LIM;
		oldest = (oldest + 1) % LIM;
	}
}

Contact PhoneBook::search(int index) {
	if (index >= 0 && index < size) {
		return contacts[index];
	}
	return (Contact());
}

void PhoneBook::print() const {
	std::cout << "                 PhoneBook" << std::endl;
	for (int i = 0; i < ((COL_WIDTH + 1) * 4); ++i)
		std::cout << "-";
	std::cout << std::endl;
	std::cout << std::setw(COL_WIDTH + 1) << "#|"
			  << std::setw(COL_WIDTH + 1) << "NAME|"
			  << std::setw(COL_WIDTH + 1) << "LAST NAME|"
			  << std::setw(COL_WIDTH + 1) << "NICKNAME|" << std::endl;
	for (int i = 0; i < ((COL_WIDTH + 1) * 4); ++i)
		std::cout << "-";
	std::cout << std::endl;
	for (int i = 0; i < size; ++i) {
		std::cout << std::setw(COL_WIDTH) << i  << "|";
		contacts[i].print();
	}
}
