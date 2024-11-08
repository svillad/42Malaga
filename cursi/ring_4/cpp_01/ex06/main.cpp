/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:24:26 by svilla-d          #+#    #+#             */
/*   Updated: 2024/11/08 13:24:26 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

void    complain_filter(std::string level){
    Harl harl;
    int complain_level = harl.get_complain_index(level);

    switch (complain_level) {
	case 0:
		harl.complain("DEBUG");
	case 1:
		harl.complain("INFO");
	case 2:
		harl.complain("WARNING");
	case 3:
		harl.complain("ERROR");
		break;
	default:
        std::cout << "[ Probably complaining about insignificant problems ]";
        std::cout << std::endl;
    } 
}

int main(int argc, char** argv) {
	std::string	level;

    if (argc != 2) {
		std::cerr << "\e[31m" << "Usage: " << argv[0]
				  << " LEVEL" << "\e[0m" << std::endl;
		return (1);
	}
    level = argv[1];
    complain_filter(level);
    std::cout << std::endl;
    return (0);
}
