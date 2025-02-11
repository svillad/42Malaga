#include "Functions.hpp"
#include <iostream>

Base* generate(void) {
    int r = rand() % 3;
    Base *obj = NULL;

    if (r == 0) {
        obj = new A();
    } else if (r == 1) {
        obj = new B();
    } else {
        obj = new C();
    }
    return obj;
}

void identify(Base* p) {
    if (!p) {
        std::cout << "Unknown type" << std::endl;
        return;
    }

    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    } else {
        std::cout << "Unknown type" << std::endl;
    }
}

void identify(Base& p) {
    try {
        (void) dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    } catch (...) {}

    try {
        (void) dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    } catch (...) {}

    try {
        (void) dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    } catch (...) {}

    std::cout << "Unknown type" << std::endl;
}
