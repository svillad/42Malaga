#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

void test_vector() {
    std::cout << "\n---------- Vector tests ----------" << std::endl;
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    try {
        std::vector<int>::iterator it = easyfind(vec, 20);
        std::cout << "Found in std::vector, value: " << *it << std::endl;
        int pos = std::distance(vec.begin(), it);
        std::cout << "Value found at position (index): " << pos << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        std::vector<int>::iterator it = easyfind(vec, 40);
        std::cout << "Found in std::vector, value: " << *it << std::endl;
        int pos = std::distance(vec.begin(), it);
        std::cout << "Value found at position (index): " << pos << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void test_list() {
    std::cout << "\n---------- List tests ----------" << std::endl;
    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(200);
    lst.push_back(300);

    try {
        std::list<int>::iterator it = easyfind(lst, 200);
        std::cout << "Found in std::list, value: " << *it << std::endl;
        int pos = std::distance(lst.begin(), it);
        std::cout << "Value found at position (index): " << pos << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        std::list<int>::iterator it = easyfind(lst, 999);
        std::cout << "Found in std::list, value: " << *it << std::endl;
        int pos = std::distance(lst.begin(), it);
        std::cout << "Value found at position (index): " << pos << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void test_deque() {
    std::cout << "\n---------- Deque tests ----------" << std::endl;
    std::deque<int> deq;
    deq.push_back(1);
    deq.push_back(3);
    deq.push_back(5);

    try {
        std::deque<int>::iterator it = easyfind(deq, 3);
        std::cout << "Found in std::deque, value: " << *it << std::endl;
        int pos = std::distance(deq.begin(), it);
        std::cout << "Value found at position (index): " << pos << std::endl;
    } catch(const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        std::deque<int>::iterator it = easyfind(deq, 7);
        std::cout << "Found in std::deque, value: " << *it << std::endl;
        int pos = std::distance(deq.begin(), it);
        std::cout << "Value found at position (index): " << pos << std::endl;
    } catch(const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    test_vector();
    test_list();
    test_deque();
    return 0;
}
