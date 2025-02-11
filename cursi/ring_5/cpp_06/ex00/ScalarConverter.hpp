#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include "ILogger.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>

class ScalarConverter {
private:
    ScalarConverter();
    ScalarConverter(const ScalarConverter &other);
    ScalarConverter& operator=(const ScalarConverter &other);
    ~ScalarConverter();

    static bool isCharLiteral(const std::string &input);
    static bool isIntLiteral(const std::string &input);
    static bool isFloatLiteral(const std::string &input);
    static bool isDoubleLiteral(const std::string &input);
    static bool isPseudoLiteral(const std::string &input);

    static ILogger* logger;

public:
    static void setLogger(ILogger* log);
    static void convert(const std::string &input);
};

#endif
