#include <iostream>
#include "Span.hpp"

void test_1by1() {
    std::cout << "\n---------- 1 by 1 tests ----------" << std::endl;
    Span sp(10000);
    for (int i = 0; i < 10000; i++)
        sp.addNumber(i);

    std::cout << "Shortest Span (0..9999): " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span  (0..9999): " << sp.longestSpan() << std::endl;
    
}

void test_range_values() {
    std::cout << "\n---------- Range values tests ----------" << std::endl;
    std::vector<int> v;
    for (int i = 50; i < 100; i++)
        v.push_back(i);

    Span sp2(50);
    sp2.addNumber(v.begin(), v.end());

    std::cout << "Shortest Span (50..99): " << sp2.shortestSpan() << std::endl;
    std::cout << "Longest Span  (50..99): " << sp2.longestSpan() << std::endl;
}

int main()
{
    test_1by1();
    test_range_values();
    
    return 0;
}
