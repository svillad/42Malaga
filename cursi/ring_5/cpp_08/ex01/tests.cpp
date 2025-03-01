/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:33:03 by svilla-d          #+#    #+#             */
/*   Updated: 2025/03/01 20:17:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Span.hpp"

void test_1by1() {
    std::cout << "\n---------- 1 by 1 tests ----------" << std::endl;
    Span sp(100000);
    for (int i = 0; i < 100000; i++)
        sp.addNumber(i);

    std::cout << "Shortest Span (0..99999): " << sp.shortestSpan() << std::endl;
    std::cout << "Longest Span  (0..99999): " << sp.longestSpan() << std::endl;
    
}

void test_range_values() {
    std::cout << "\n---------- Range values tests ----------" << std::endl;
    std::vector<int> v;
    for (int i = 0; i < 100; i++)
        v.push_back(i);

    Span sp2(50);
    sp2.addNumber(v.begin() + 50, v.end());

    std::cout << "Shortest Span (50..99): " << sp2.shortestSpan() << std::endl;
    std::cout << "Longest Span  (50..99): " << sp2.longestSpan() << std::endl;
}

void test_overflow()
{
    std::cout << "\n---------- Error tests ----------" << std::endl;
    Span sp = Span(5);
    try {
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        sp.addNumber(12);

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    } catch(std::runtime_error &e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void test_one_element()
{
    std::cout << "\n---------- One Element tests ----------" << std::endl;
    Span sp = Span(2);
    try {
        sp.addNumber(6);
        std::cout << sp.shortestSpan() << std::endl;
    } catch(std::runtime_error &e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    try {
        std::cout << sp.longestSpan() << std::endl;
    } catch(std::runtime_error &e){
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

int main()
{
    test_1by1();
    test_range_values();
    test_overflow();
    test_one_element();
    
    return 0;
}
