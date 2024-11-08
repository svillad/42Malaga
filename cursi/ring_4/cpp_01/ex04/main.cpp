/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:22:54 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:55 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "FileManager.hpp"

int main(int argc, char** argv) {
	std::string	filename;
	std::string	s1;
	std::string	s2;

	if (argc != 4) {
		std::cerr << "\e[31m" << "Usage: " << argv[0]
				  << " <filename> <s1> <s2>" << "\e[0m" << std::endl;
		return (1);
	}
	filename = argv[1];
	s1 = argv[2];
	s2 = argv[3];
	FileManager filemanager(filename, s1, s2);
	if (!filemanager.replace_in_file())
		return (1);
	std::cout << "\e[32mSuccessful replacement\e[0m" << std::endl;
	return (0);
}
