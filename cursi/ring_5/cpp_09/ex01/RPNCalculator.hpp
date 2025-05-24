/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPNCalculator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:02:43 by svilla-d          #+#    #+#             */
/*   Updated: 2025/05/24 18:02:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPNCALCULATOR_HPP
#define RPNCALCULATOR_HPP

#include <string>
#include <vector>

class RPNCalculator {
private:
    std::string expression;
    std::vector<std::string> tokens;

    void tokenize();
    bool isOperator(const std::string &token) const;
    double applyOperator(char op, double a, double b) const;
    bool isNumber(const std::string &token) const;

public:
    RPNCalculator();
    RPNCalculator(const std::string &expression);
    RPNCalculator(const RPNCalculator &other);
    RPNCalculator &operator=(const RPNCalculator &other);
    ~RPNCalculator();

    const std::vector<std::string>& getTokens() const;
    void printTokens() const;
    double evaluate() const;
};

#endif
