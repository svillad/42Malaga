#include "Harl.hpp"

int main() {
    Harl harl;
    harl.complain("DEBUG");
    std::cout << std::endl;
    harl.complain("INFO");
    std::cout << std::endl;

    Harl harlCopy(harl);
    harlCopy.complain("WARNING");
    std::cout << std::endl;

    Harl anotherHarl;
    anotherHarl = harl;
    anotherHarl.complain("ERROR");
    std::cout << std::endl;

    harl.complain("UNKNOWN");
    return 0;
}
