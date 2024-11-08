/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:24:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:24:19 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() {
	levels[0] = "DEBUG";
	levels[1] = "INFO";
	levels[2] = "WARNING";
	levels[3] = "ERROR";

	actions[0] = &Harl::debug;
	actions[1] = &Harl::info;
	actions[2] = &Harl::warning;
	actions[3] = &Harl::error;
}

void Harl::debug(void) {
	std::cout << "\e[34m[ DEBUG ]\e[0m" << std::endl;
	std::cout << "I love having extra bacon for my "
		"7XL-double-cheese-triple-pickle-special-ketchup burger. "
		"I really do!" << std::endl;
}

void Harl::info(void) {
	std::cout << "\e[32m[ INFO ]\e[0m" << std::endl;
	std::cout << "I cannot believe adding extra bacon "
		"costs more money. You didn’t put enough bacon in my burger! "
		"If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning(void) {
	std::cout << "\e[33m[ WARNING ]\e[0m" << std::endl;
	std::cout << "I think I deserve to have some extra "
		"bacon for free. I’ve been coming for years whereas you started "
		"working here last month." << std::endl;
}

void Harl::error(void) {
	std::cout << "\e[31m[ ERROR ]\e[0m" << std::endl;
	std::cout << "This is unacceptable! I want to speak "
		"to the manager now." << std::endl;
}

int	Harl::get_complain_index(std::string level) {
	for (int i = 0; i < 4; i++) {
		if (levels[i] == level) {
			return (i);
		}
	}
	return (-1);
}

void Harl::complain(std::string level) {
	int	complain_level = get_complain_index(level);
	if (complain_level < 0 || complain_level > LEVELS) {
		std::cout << "\e[35m[ UNKNOWN ]\e[0m" << std::endl;
		std::cout << "The complaint level provided is invalid."
				<< std::endl;
		return;
	}
	(this->*actions[complain_level])();
}
