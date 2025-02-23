/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 16:21:25 by svilla-d          #+#    #+#             */
/*   Updated: 2025/02/23 18:15:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include "ILogger.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <limits>
#include <cmath>
#include <iomanip>
#include <cerrno>
#include <cctype>

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
    static ILogger* getLogger();
    static void convert(const std::string &input);
};

#endif
