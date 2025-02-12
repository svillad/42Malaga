#include "templates.hpp"
#include "Point.hpp"
#include <iostream>
#include <string>

int main() {
    std::cout << "\n---------- Int's tests ----------" << std::endl;
    int x = 10, y = 20;
    std::cout << "Before swap: x = " << x << ", y = " << y << std::endl;
    swap(x, y);
    std::cout << "After swap: x = " << x << ", y = " << y << std::endl;
    std::cout << "Min(x, y): " << min(x, y) << std::endl;
    std::cout << "Max(x, y): " << max(x, y) << std::endl;

    std::cout << "\n---------- Float's tests ----------" << std::endl;
    float f1 = 4.5f, f2 = 5.4f;
    std::cout << "Before swap: f1 = " << f1 << ", f2 = " << f2 << std::endl;
    swap(f1, f2);
    std::cout << "After swap: f1 = " << f1 << ", f2 = " << f2 << std::endl;
    std::cout << "Min(f1, f2): " << min(f1, f2) << std::endl;
    std::cout << "Max(f1, f2): " << max(f1, f2) << std::endl;

    std::cout << "\n---------- Char's tests ----------" << std::endl;
    char a = 'A', b = 'Z';
    std::cout << "Before swap: a = " << a << ", b = " << b << std::endl;
    swap(a, b);
    std::cout << "After swap: a = " << a << ", b = " << b << std::endl;
    std::cout << "Min(a, b): " << min(a, b) << std::endl;
    std::cout << "Max(a, b): " << max(a, b) << std::endl;
    
    std::cout << "\n---------- Boolean's tests ----------" << std::endl;
    bool t = true, f = false;
    std::cout << "Before swap: t = " << t << ", f = " << f << std::endl;
    swap(t, f);
    std::cout << "After swap: t = " << t << ", f = " << f << std::endl;
    std::cout << "Min(t, f): " << min(t, f) << std::endl;
    std::cout << "Max(t, f): " << max(t, f) << std::endl;

    std::cout << "\n---------- String's tests ----------" << std::endl;
    std::string str1 = "apple", str2 = "banana";
    std::cout << "Before swap: str1 = " << str1 << ", str2 = " << str2 << std::endl;
    swap(str1, str2);
    std::cout << "After swap: str1 = " << str1 << ", str2 = " << str2 << std::endl;
    std::cout << "Min(str1, str2): " << ::min(str1, str2) << std::endl;
    std::cout << "Max(str1, str2): " << ::max(str1, str2) << std::endl;

    std::cout << "\n---------- Object's tests ----------" << std::endl;
    Point p1(3, 4), p2(5, 6);
    std::cout << "Before swap: p1 = " << p1 << ", p2 = " << p2 << std::endl;
    swap(p1, p2);
    std::cout << "After swap: p1 = " << p1 << ", p2 = " << p2 << std::endl;
    std::cout << "Min(p1, p2): " << min(p1, p2) << std::endl;
    std::cout << "Max(p1, p2): " << max(p1, p2) << std::endl;

    return 0;
}
