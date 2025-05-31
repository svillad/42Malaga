/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPNCalculator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:02:43 by svilla-d          #+#    #+#             */
/*   Updated: 2025/05/31 19:40:00 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPNCALCULATOR_HPP
#define RPNCALCULATOR_HPP

#include <string>
#include <stack>

class RPNCalculator {
private:
    std::string             expression;
    std::stack<std::string> stack;

    void   tokenize();
    bool   isOperator(const std::string &t) const;
    bool   isNumber(const std::string &t) const;
    double applyOperator(char op, double a, double b) const;
    double compute();

public:
    RPNCalculator();
    explicit RPNCalculator(const std::string &expression);
    RPNCalculator(const RPNCalculator &other);
    RPNCalculator &operator=(const RPNCalculator &other);
    ~RPNCalculator();

    void   setExpression(const std::string &expr);
    double evaluate();
};

#endif
