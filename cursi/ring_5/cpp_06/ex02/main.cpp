#include "Functions.hpp"
#include <iostream>
#include <ctime>

int main() {
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
