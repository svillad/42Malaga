/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:39:32 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:39:33 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Functions.hpp"
#include <iostream>
#include <ctime>

int main() {
    srand(time(NULL));
    std::cout << "\n---------- Generating Random Base Objects ----------\n" << std::endl;
    for (int i = 0; i < 5; i++) {
        std::cout << "* Creating instance" << std::endl;
        Base* obj = generate();
        
        std::cout << "  - Pointer identify: ";
        identify(obj);

        std::cout << "  - Reference identify: ";
        identify(*obj);

        delete obj;
        std::cout << std::endl;
    }

    std::cout << "\n---------- Null Object ----------\n" << std::endl;
    std::cout << "* Creating instance" << std::endl;
    std::cout << "  - Pointer/Reference identify: ";
    identify(NULL);

    return 0;
}
