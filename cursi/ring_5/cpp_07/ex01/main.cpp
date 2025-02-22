/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:53:43 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:53:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
#include "Point.hpp"
#include <iostream>

int main() {
    std::cout << "\n---------- Int Array's tests ----------" << std::endl;
    int intArray[] = {1, 2, 3, 4, 5};
    size_t intArraySize = sizeof(intArray) / sizeof(intArray[0]);

    std::cout << "Original intArray: ";
    iter(intArray, intArraySize, printElement<int>);
    std::cout << std::endl;

    iter(intArray, intArraySize, incrementElement<int>);
    std::cout << "After increment: ";
    iter(intArray, intArraySize, printElement<int>);
    std::cout << std::endl;

    iter(intArray, intArraySize, doubleElement<int>);
    std::cout << "After doubling: ";
    iter(intArray, intArraySize, printElement<int>);
    std::cout << std::endl;

    std::cout << "\n---------- Char Array's tests ----------" << std::endl;
    char charArray[] = {'a', 'b', 'c', 'd', 'e'};
    size_t charArraySize = sizeof(charArray) / sizeof(charArray[0]);

    std::cout << "Original charArray: ";
    iter(charArray, charArraySize, printElement<char>);
    std::cout << std::endl;

    iter(charArray, charArraySize, incrementElement<char>);
    std::cout << "After increment: ";
    iter(charArray, charArraySize, printElement<char>);
    std::cout << std::endl;

    std::cout << "\n---------- String Array's tests ----------" << std::endl;
    std::string strArray[] = {"apple", "banana", "cherry"};
    size_t strArraySize = sizeof(strArray) / sizeof(strArray[0]);

    std::cout << "Original strArray: ";
    iter(strArray, strArraySize, printElement<std::string>);
    std::cout << std::endl;

    std::cout << "\n---------- Object Array's tests ----------" << std::endl;
    Point pointArray[] = {Point(3,4), Point(5,6), Point(7,8)};
    size_t pointArraySize = sizeof(pointArray) / sizeof(pointArray[0]);

    std::cout << "Original pointArray: ";
    iter(pointArray, pointArraySize, printElement<Point>);
    std::cout << std::endl;

    iter(pointArray, pointArraySize, incrementElement<Point>);
    std::cout << "After increment: ";
    iter(pointArray, pointArraySize, printElement<Point>);
    std::cout << std::endl;

    iter(pointArray, pointArraySize, doubleElement<Point>);
    std::cout << "After doubling: ";
    iter(pointArray, pointArraySize, printElement<Point>);
    std::cout << std::endl;

    return 0;
}
