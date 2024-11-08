/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:12:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:12:16 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact()
	: first_name(""), last_name(""), nickname(""),
	  phone_number(""), darkest_secret("") {}

Contact::Contact(const Contact& c)
	: first_name(c.first_name), last_name(c.last_name),
	  nickname(c.nickname), phone_number(c.phone_number),
	  darkest_secret(c.darkest_secret) {}

Contact::Contact(const std::string& first_name, const std::string& last_name,
				 const std::string& nickname, const std::string& phone_number,
				 const std::string& darkest_secret)
	: first_name(first_name), last_name(last_name), nickname(nickname),
	  phone_number(phone_number), darkest_secret(darkest_secret) {}

Contact&	Contact::operator=(const Contact& c) {
	if (this != &c) {
		first_name = c.first_name;
		last_name = c.last_name;
		nickname = c.nickname;
		phone_number = c.phone_number;
		darkest_secret = c.darkest_secret;
	}
	return (*this);
}

bool	Contact::set_field(const std::string& field_name, std::string* field) {
	std::string temp;
	do {
		std::cout << "Please enter " << field_name << ": ";
		std::getline(std::cin, temp);
		
		bool isOnlySpaces = true;
		for (size_t i = 0; i < temp.length(); ++i) {
			if (!isspace(temp[i])) {
				isOnlySpaces = false;
				break;
			}
		}
		if (!temp.empty() && !isOnlySpaces) {
			*field = temp;
			return (true);
		} else
			std::cout << "Invalid value. The value cannot be empty or contain "
						 "only spaces." << std::endl;
	} while (true);
	return (false);
}

const std::string&	Contact::get_first_name() const {
	return (first_name);
}

const std::string&	Contact::get_last_name() const {
	return (last_name);
}

const std::string&	Contact::get_nickname() const {
	return (nickname);
}

const std::string&	Contact::get_phone_number() const {
	return (phone_number);
}

const std::string&	Contact::get_darkest_secret() const {
	return (darkest_secret);
}

void Contact::create() {
	set_field("first name", &first_name);
	set_field("last name", &last_name);
	set_field("nickname", &nickname);
	set_field("phone number", &phone_number);
	set_field("darkest secret", &darkest_secret);
}

void Contact::print() const {
	std::cout << formatColumn(first_name) << "|"
			  << formatColumn(last_name) << "|"
			  << formatColumn(nickname) << "|"
			  << std::endl;
}

void Contact::print_full() const {
	std::cout << std::setw(16) << "NAME: " << first_name << std::endl;
	std::cout << std::setw(16) << "LAST NAME: "<< last_name << std::endl;
	std::cout << std::setw(16) << "NICKNAME: "<< nickname << std::endl;
	std::cout << std::setw(16) << "PHONE NUMBER: "<< phone_number << std::endl;
	std::cout << std::setw(16) << "DARKEST SECRET: "<< darkest_secret << std::endl;
}

std::string formatColumn(const std::string& text) {
	std::string formatted;

	if (text.length() > COL_WIDTH)
		return (text.substr(0, COL_WIDTH - 1) + '.');
	formatted = text;
	while (formatted.length() < COL_WIDTH)
		formatted = " " + formatted;
	return (formatted);
}
