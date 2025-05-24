/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:02:30 by svilla-d          #+#    #+#             */
/*   Updated: 2025/05/24 18:02:32 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPNCalculator.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " \"expresion RPN\"" << std::endl;
        return 1;
    }
    
    std::string expression = argv[1];
    RPNCalculator calculator(expression);
        
    double result = calculator.evaluate();
    std::cout << "Resultado: " << result << std::endl;
    
    return 0;
}
