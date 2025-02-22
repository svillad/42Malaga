/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:21:22 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/22 16:21:23 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

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

bool ScalarConverter::isCharLiteral(const std::string &input) {
    return input.length() == 1 && !isdigit(input[0]);
}

bool ScalarConverter::isIntLiteral(const std::string &input) {
    std::istringstream iss(input);
    int value;
    return (iss >> value) && (iss.eof());
}

bool ScalarConverter::isFloatLiteral(const std::string &input) {
    if (input == "-inff" || input == "+inff" || input == "nanf")
        return true;
    if (input.find('f') == std::string::npos) return false;
    
    std::istringstream iss(input.substr(0, input.length() - 1));
    float value;
    return (iss >> value) && (iss.eof());
}

bool ScalarConverter::isDoubleLiteral(const std::string &input) {
    if (input == "-inf" || input == "+inf" || input == "nan")
        return true;
    
    std::istringstream iss(input);
    double value;
    return (iss >> value) && (iss.eof());
}

bool ScalarConverter::isPseudoLiteral(const std::string &input) {
    return (input == "-inf" || input == "+inf" || input == "nan" || 
            input == "-inff" || input == "+inff" || input == "nanf");
}

void ScalarConverter::convert(const std::string &input) {
    if (logger)
        logger->log(INFO, "[ScalarConverter] Converting: " + input);

    if (isPseudoLiteral(input)) {
        if (logger)
            logger->log(INFO, "[ScalarConverter] ✅ PseudoLiteral");
        std::string cleanInput = (input[input.length() - 1] == 'f') ? input.substr(0, input.length() - 1) : input;
        std::cout << "char: impossible" << std::endl;
        std::cout << "int: impossible" << std::endl;
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: " << cleanInput << "f" << std::endl;
        std::cout << "double: " << cleanInput << std::endl;
        return;
    } else if (logger)
        logger->log(INFO, "[ScalarConverter] ❌ PseudoLiteral");

    if (isCharLiteral(input)) {
        if (logger)
            logger->log(INFO, "[ScalarConverter] ✅ CharLiteral");
        char c = input[0];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
        return;
    } else if (logger)
        logger->log(INFO, "[ScalarConverter] ❌ CharLiteral");

    if (isIntLiteral(input)) {
        if (logger)
            logger->log(INFO, "[ScalarConverter] ✅ IntLiteral");
        int i = std::atoi(input.c_str());
        std::cout << "char: " << ((i >= 32 && i <= 126) ? std::string(1, static_cast<char>(i)) : "Non displayable") << std::endl;
        std::cout << "int: " << i << std::endl;
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: " << static_cast<float>(i) << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(i) << std::endl;
        return;
    } else if (logger)
        logger->log(INFO, "[ScalarConverter] ❌ IntLiteral");

    if (isFloatLiteral(input)) {
        if (logger)
            logger->log(INFO, "[ScalarConverter] ✅ FloatLiteral");
        float f = std::strtof(input.c_str(), NULL);
        int i = static_cast<int>(f);
        std::cout << "char: " << ((i >= 32 && i <= 126) ? std::string(1, static_cast<char>(i)) : "Non displayable") << std::endl;
        std::cout << "int: " << i << std::endl;
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: " << f << "f" << std::endl;
        std::cout << "double: " << static_cast<double>(f) << std::endl;
        return;
    } else if (logger)
        logger->log(INFO, "[ScalarConverter] ❌ FloatLiteral");


    if (isDoubleLiteral(input)) {
        if (logger)
            logger->log(INFO, "[ScalarConverter] ✅ DoubleLiteral");
        double d = std::strtod(input.c_str(), NULL);
        int i = static_cast<int>(d);
        std::cout << "char: " << ((i >= 32 && i <= 126) ? std::string(1, static_cast<char>(i)) : "Non displayable") << std::endl;
        std::cout << "int: " << i << std::endl;
        std::cout << std::fixed << std::setprecision(1);
        std::cout << "float: " << static_cast<float>(d) << "f" << std::endl;
        std::cout << "double: " << d << std::endl;
        return;
    } else if (logger)
        logger->log(INFO, "[ScalarConverter] ❌ DoubleLiteral");

    if (logger)
        logger->log(ERROR, "[ScalarConverter] ❌ Invalid input: " + input);
    
    std::cout << "Error: Invalid input format" << std::endl;
}
