#include <iostream>
#include <string>
#include "RPNCalculator.hpp"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " \"expresion RPN\"" << std::endl;
        return 1;
    }
    
    std::string expression = argv[1];
    RPNCalculator calculator(expression);
    
    // Descomenta la siguiente línea si deseas ver los tokens:
    // calculator.printTokens();
    
    double result = calculator.evaluate();
    std::cout << "Resultado: " << result << std::endl;
    
    return 0;
}
