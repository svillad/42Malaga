/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:12:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/23 17:50:54 by svilla-d         ###   ########.fr       */
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

std::string Contact::format_field(const std::string &str) {
    std::string result;
    bool in_space = false;

    size_t start = 0;
    while (start < str.length() && std::isspace(str[start])) {
        ++start;
    }

    for (size_t i = start; i < str.length(); ++i) {
        if (std::isspace(str[i])) {
            if (!in_space) {
                result += ' ';
                in_space = true;
            }
        } else {
            result += str[i];
            in_space = false;
        }
    }

    while (!result.empty() && std::isspace(result[result.length() - 1])) {
        result.resize(result.length() - 1);
    }
    return result;
}

bool	Contact::set_field(const std::string& field_name, std::string* field) {
	std::string temp;
	do {
		std::cout << "Please enter " << field_name << ": ";
		if (!std::getline(std::cin, temp)) {
            if (std::cin.eof()) {
                std::cout << "\nEOF reached. Exiting the program." << std::endl;
                break;
            }
            std::cerr << "Invalid value. Please try again with a valid value." << std::endl;
            continue;
        }
		bool isOnlySpaces = true;
		for (size_t i = 0; i < temp.length(); ++i) {
			if (!isspace(temp[i])) {
				isOnlySpaces = false;
				break;
			}
		}
		if (!temp.empty() && !isOnlySpaces) {
			*field = format_field(temp);
			return (true);
		} else
			std::cout << "Invalid value. The value cannot be empty or contain "
						 "only spaces." << std::endl;
	} while (true);
	return (false);
}

bool Contact::set_number(const std::string& name, std::string* field) {
    std::string temp;
    do {
        temp.clear();
        std::cout << "Please enter " << name << ": ";
        if (!std::getline(std::cin, temp)) {
            if (std::cin.eof()) {
                std::cout << "\nEOF reached. Exiting the program." << std::endl;
                break;
            }
            std::cerr << "Invalid value. Please try again with a valid value." << std::endl;
            continue;
        }
        if (!trim_spaces(temp)) {
            std::cout << "Invalid value. The value cannot be empty or contain only spaces." << std::endl;
            continue;
        }
        if (!is_valid_number_format(temp))
            continue;
        if (!validate_number(temp))
            continue;
        *field = format_field(temp);
        return true;
    } while (true);
    return false;
}


bool Contact::trim_spaces(std::string& temp) {
    size_t start = 0;
    while (start < temp.length() && std::isspace(temp[start])) {
        ++start;
    }

    size_t end = temp.length() - 1;
    while (end > start && std::isspace(temp[end])) {
        --end;
    }

    if (start > end) {
        return false;
    }

    temp = temp.substr(start, end - start + 1);
    return true;
}

bool Contact::is_valid_number_format(const std::string& temp) {
    if (temp[0] == '+') {
        for (size_t i = 1; i < temp.length(); ++i) {
            if (temp[i] == '+') {
                std::cout << "Invalid value. The value cannot have more than one '+'." << std::endl;
                return false;
            }
			if (!(std::isdigit(temp[i]) || std::isspace(temp[i]))) {
            	std::cout << "Invalid value. The value must contain only numbers or the '+' sign." << std::endl;
            	return false;
        	}
        }
		return true;
    }

    for (size_t i = 0; i < temp.length(); ++i) {
		if (temp[i] == '+') {
			std::cout << "Invalid value. The value can only have a '+' sign at the beginning of the number." << std::endl;
			return false;
		}
        if (!(std::isdigit(temp[i]) || std::isspace(temp[i]))) {
            std::cout << "Invalid value. The value must contain only numbers or the '+' sign." << std::endl;
            return false;
        }
    }
    return true;
}

bool Contact::validate_number(const std::string& temp) {
    bool hasNumber = false;

    for (size_t i = 0; i < temp.length(); ++i) {
        if (std::isdigit(temp[i])) {
            hasNumber = true;
            break;
        }
    }
    if (!hasNumber) {
        std::cout << "Invalid value. The value must include at least one number." << std::endl;
    }
    return hasNumber;
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

bool Contact::create() {
	if(!set_field("first name", &first_name))
		return false;
	if(!set_field("last name", &last_name))
		return false;
	if(!set_field("nickname", &nickname))
		return false;
	if(!set_number("phone number", &phone_number))
		return false;
	if(!set_field("darkest secret", &darkest_secret))
		return false;
	return true;
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

void clear_buffer(void) {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}