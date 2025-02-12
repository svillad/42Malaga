#include <iostream>
#include "Array.hpp"
#include "Point.hpp"

int main() {
    std::cout << "\n---------- Int Array's tests ----------" << std::endl;
    Array<int> intArray(5);
    for (unsigned int i = 0; i < intArray.size(); i++) {
        intArray[i] = i * 10;
    }
    for (unsigned int i = 0; i < intArray.size(); i++) {
        std::cout << "intArray[" << i << "] = " << intArray[i] << std::endl;
    }

    std::cout << "\n---------- Char Array's tests ----------" << std::endl;
    Array<char> charArray(5);
    for (unsigned int i = 0; i < charArray.size(); i++) {
        charArray[i] = 'A' + i;
    }
    for (unsigned int i = 0; i < charArray.size(); i++) {
        std::cout << "charArray[" << i << "] = " << charArray[i] << std::endl;
    }

    std::cout << "\n---------- String Array's tests ----------" << std::endl;
    Array<std::string> strArray(3);
    strArray[0] = "Hello";
    strArray[1] = "World";
    strArray[2] = "!";
    for (unsigned int i = 0; i < strArray.size(); i++) {
        std::cout << "strArray[" << i << "] = " << strArray[i] << std::endl;
    }

    std::cout << "\n---------- Object Array's tests ----------" << std::endl;
    Array<Point> pointArray(3);
    pointArray[0] = Point(1, 2);
    pointArray[1] = Point(3, 4);
    pointArray[2] = Point(5, 6);
    for (unsigned int i = 0; i < pointArray.size(); i++) {
        std::cout << "pointArray[" << i << "] = " << pointArray[i] << std::endl;
    }

    std::cout << "\n---------- Overload Constructor's tests ----------" << std::endl;
    Array<Point> pointArray2(pointArray);
    for (unsigned int i = 0; i < pointArray2.size(); i++) {
        std::cout << "pointArray2[" << i << "] = " << pointArray2[i] << std::endl;
    }

    Array<Point> pointArray3;
    pointArray3 = pointArray;
    for (unsigned int i = 0; i < pointArray3.size(); i++) {
        std::cout << "pointArray3[" << i << "] = " << pointArray3[i] << std::endl;
    }

    std::cout << "\n---------- Const Array's tests ----------" << std::endl;
    int values[] = {1, 2, 3, 4};
    const Array<int> constArray(4, values);
    for (unsigned int i = 0; i < constArray.size(); i++) {
        std::cout << "constArray[" << i << "] = " << constArray[i] << std::endl;
    }

    const Array<int> constIntArray(3, intArray);
    for (unsigned int i = 0; i < constIntArray.size(); i++) {
        std::cout << "constIntArray[" << i << "] = " << constIntArray[i] << std::endl;
    }

    std::cout << "\n---------- Exception's tests ----------" << std::endl;
    try {
        intArray[-2] = 0;
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    try {
        pointArray[4] = Point(0,0);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
