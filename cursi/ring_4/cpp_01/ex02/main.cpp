/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:13 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:13 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(void) {
	std::string str = "HI THIS IS BRAIN";

	std::string *stringPTR = &str;
	std::string &stringREF = str;

	std::cout << "Memory address by variable:  " << &str << std::endl;
	std::cout << "Memory address by stringPTR: " << stringPTR << std::endl;
	std::cout << "Memory address by stringREF: " << &stringREF << std::endl;
	std::cout << std::endl;
	std::cout << "Value string by variable:  " << str << std::endl;
	std::cout << "Value string by stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value string by stringREF: " << stringREF << std::endl;
	return (0);
}
