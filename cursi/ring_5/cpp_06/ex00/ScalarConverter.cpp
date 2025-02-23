/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:21:22 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:21:23 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

//--------------------------------------------------------------------------
// Aux Functions
//--------------------------------------------------------------------------

static int getDecimalPrecision(const std::string &input) {
    size_t dotPos = input.find('.');
    if (dotPos == std::string::npos)
        return 1;
    
    size_t endPos = input.size();
    if (!input.empty() && input.back() == 'f')
        endPos = input.size() - 1;
    
    int precision = 0;
    for (size_t i = dotPos + 1; i < endPos; ++i) {
        if (std::isdigit(input[i]))
            precision++;
        else
            break;
    }
    return (precision == 0) ? 1 : precision;
}

static std::string getIntegerPart(const std::string &input) {
    size_t i = 0;
    if (i < input.size() && (input[i] == '+' || input[i] == '-'))
        i++;
    std::string integerPart;
    while (i < input.size() && std::isdigit(input[i])) {
        integerPart.push_back(input[i]);
        i++;
    }

    size_t pos = 0;
    while (pos < integerPart.size() && integerPart[pos] == '0')
        pos++;
    return (pos < integerPart.size()) ? integerPart.substr(pos) : "0";
}

static void printImpossible() {
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << "float: impossible" << std::endl;
    std::cout << "double: impossible" << std::endl;
}

//--------------------------------------------------------------------------
// Convert Functions
//--------------------------------------------------------------------------

static void convertPseudoLiteral(const std::string &input) {
    if (ScalarConverter::getLogger())
        ScalarConverter::getLogger()->log(INFO, "[ScalarConverter] ✅ PseudoLiteral");
    std::string cleanInput = (input[input.length() - 1] == 'f' && input[input.length() - 2] == 'f') ? input.substr(0, input.length() - 1) : input;
    std::cout << "char: impossible" << std::endl;
    std::cout << "int: impossible" << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << cleanInput << "f" << std::endl;
    std::cout << "double: " << cleanInput << std::endl;
}

static void convertCharLiteral(const std::string &input) {
    if (ScalarConverter::getLogger())
        ScalarConverter::getLogger()->log(INFO, "[ScalarConverter] ✅ CharLiteral");
    char c = input[0];
    std::cout << "char: '" << c << "'" << std::endl;
    std::cout << "int: " << static_cast<int>(c) << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(c) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(c) << std::endl;
}

static void convertIntLiteral(const std::string &input) {
    if (ScalarConverter::getLogger())
        ScalarConverter::getLogger()->log(INFO, "[ScalarConverter] ✅ IntLiteral");
    errno = 0;
    char* end;
    long long ll = std::strtoll(input.c_str(), &end, 10);
    if (errno == ERANGE || ll > std::numeric_limits<int>::max() || ll < std::numeric_limits<int>::min()) {
        if (ScalarConverter::getLogger())
            ScalarConverter::getLogger()->log(ERROR, "[ScalarConverter] int overflow");
        printImpossible();
        return;
    }
    int i = static_cast<int>(ll);
    std::cout << "char: " 
              << ((i >= 32 && i <= 126) ? ("'" + std::string(1, static_cast<char>(i)) + "'") : "Non displayable") 
              << std::endl;
    std::cout << "int: " << i << std::endl;
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "float: " << static_cast<float>(i) << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(i) << std::endl;
}

static void convertFloatLiteral(const std::string &input) {
    if (ScalarConverter::getLogger())
        ScalarConverter::getLogger()->log(INFO, "[ScalarConverter] ✅ FloatLiteral");
    std::string numPart = input;
    if (!numPart.empty() && numPart.back() == 'f')
        numPart = numPart.substr(0, numPart.size()-1);
    
    errno = 0;
    char* end;
    float f = std::strtof(numPart.c_str(), &end);
    if (errno == ERANGE) {
        if (ScalarConverter::getLogger())
            ScalarConverter::getLogger()->log(ERROR, "[ScalarConverter] float overflow");
        printImpossible();
        return;
    }

    if (f > static_cast<float>(std::numeric_limits<int>::max()) ||
        f < static_cast<float>(std::numeric_limits<int>::min())) {
        std::cout << "char: Non displayable" << std::endl;
        std::cout << "int: impossible" << std::endl;
    } else {
        int i = static_cast<int>(f);
        std::cout << "char: " 
              << ((i >= 32 && i <= 126) ? ("'" + std::string(1, static_cast<char>(i)) + "'") : "Non displayable")
              << std::endl;
        std::cout << "int: " << i << std::endl;
    }
    int prec = getDecimalPrecision(numPart);
    std::cout << std::fixed << std::setprecision(prec);
    std::cout << "float: " << f << "f" << std::endl;
    std::cout << "double: " << static_cast<double>(f) << std::endl;
}

static void convertDoubleLiteral(const std::string &input) {
    if (ScalarConverter::getLogger())
        ScalarConverter::getLogger()->log(INFO, "[ScalarConverter] ✅ DoubleLiteral");
    errno = 0;
    char* end;
    double d = std::strtod(input.c_str(), &end);
    if (errno == ERANGE) {
        if (ScalarConverter::getLogger())
            ScalarConverter::getLogger()->log(ERROR, "[ScalarConverter] double overflow");
        printImpossible();
        return;
    }

    if (d > static_cast<double>(std::numeric_limits<int>::max()) ||
        d < static_cast<double>(std::numeric_limits<int>::min())) {
         std::cout << "char: Non displayable" << std::endl;
         std::cout << "int: impossible" << std::endl;
    } else {
         int i = static_cast<int>(d);
         std::cout << "char: " 
              << ((i >= 32 && i <= 126) ? ("'" + std::string(1, static_cast<char>(i)) + "'") : "Non displayable")
              << std::endl;
         std::cout << "int: " << i << std::endl;
    }
    int prec = getDecimalPrecision(input);
    std::cout << std::fixed << std::setprecision(prec);
    std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
    std::cout << "double: " << d << std::endl;
}

//--------------------------------------------------------------------------
// Methods ScalarConverter Class
//--------------------------------------------------------------------------

ILogger* ScalarConverter::logger = NULL;

ScalarConverter::ScalarConverter() {
}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
    (void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
    (void)other;
    return *this;
}

ScalarConverter::~ScalarConverter() {
}

void ScalarConverter::setLogger(ILogger* log) {
    logger = log;
    if (logger)
        logger->log(DEBUG, "[ScalarConverter] Logger initialized.");
}

ILogger* ScalarConverter::getLogger() {
    return logger;
}

bool ScalarConverter::isCharLiteral(const std::string &input) {
    return input.length() == 1 && !std::isdigit(input[0]);
}

bool ScalarConverter::isIntLiteral(const std::string &input) {
    errno = 0;
    char* end;
    std::strtoll(input.c_str(), &end, 10);
    return (errno != ERANGE && *end == '\0');
}

bool ScalarConverter::isFloatLiteral(const std::string &input) {
    if (input == "-inff" || input == "+inff" || input == "nanf")
        return true;
    if (input.find('f') == std::string::npos)
        return false;
    std::string numPart = input.substr(0, input.size() - 1);
    errno = 0;
    char* end;
    std::strtof(numPart.c_str(), &end);
    return (errno != ERANGE && *end == '\0');
}

bool ScalarConverter::isDoubleLiteral(const std::string &input) {
    if (input == "-inf" || input == "+inf" || input == "nan")
        return true;
    errno = 0;
    char* end;
    std::strtod(input.c_str(), &end);
    return (errno != ERANGE && *end == '\0');
}

bool ScalarConverter::isPseudoLiteral(const std::string &input) {
    return (input == "-inf" || input == "+inf" || input == "nan" ||
            input == "-inff" || input == "+inff" || input == "nanf");
}

void ScalarConverter::convert(const std::string &input) {
    if (logger)
        logger->log(INFO, "[ScalarConverter] Converting: " + input);

    if (!isPseudoLiteral(input) && !isCharLiteral(input)) {
        std::string intPart = getIntegerPart(input);
        if (intPart.size() > 10) {
            if (logger)
                logger->log(ERROR, "[ScalarConverter] Invalid input format");
            std::cout << "Error: Number is too long" << std::endl;
            return;
        }
    }

    if (isPseudoLiteral(input))
        convertPseudoLiteral(input);
    else if (isCharLiteral(input))
        convertCharLiteral(input);
    else if (isIntLiteral(input))
        convertIntLiteral(input);
    else if (isFloatLiteral(input))
        convertFloatLiteral(input);
    else if (isDoubleLiteral(input))
        convertDoubleLiteral(input);
    else {
        if (logger)
            logger->log(ERROR, "[ScalarConverter] ❌ Invalid input: " + input);
        std::cout << "Error: Invalid input format" << std::endl;
    }
}
