/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPNCalculator.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:02:43 by svilla-d          #+#    #+#             */
/*   Updated: 2025/05/31 19:40:02 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPNCalculator.hpp"
#include <sstream>
#include <iostream>
#include <cstdlib>

RPNCalculator::RPNCalculator() : expression("") {
}

RPNCalculator::RPNCalculator(const std::string &expr) : expression(expr) {
}

RPNCalculator::RPNCalculator(const RPNCalculator &other)
    : expression(other.expression), stack(other.stack) {
}

RPNCalculator &RPNCalculator::operator=(const RPNCalculator &other) {
    if (this != &other) {
        expression = other.expression;
        stack      = other.stack;
    }
    return *this;
}

RPNCalculator::~RPNCalculator() {
}

void RPNCalculator::tokenize() {
    while (!stack.empty())
        stack.pop();

    std::istringstream iss(expression);
    std::string tok;
    while (iss >> tok)
        stack.push(tok);
}

bool RPNCalculator::isOperator(const std::string &t) const {
    return t.size() == 1 && (t[0] == '+' || t[0] == '-' ||
                             t[0] == '*' || t[0] == '/');
}

bool RPNCalculator::isNumber(const std::string &t) const {
    if (t.empty())
        return false;
    std::istringstream iss(t);
    double d;
    iss >> d;
    return iss.eof() && !iss.fail();
}

double RPNCalculator::applyOperator(char op, double a, double b) const {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                std::cerr << "Error: division by zero." << std::endl;
                std::exit(EXIT_FAILURE);
            }
            return a / b;
        default:
            std::cerr << "Error: unknown operator '" << op << "'." << std::endl;
            std::exit(EXIT_FAILURE);
    }
}

double RPNCalculator::compute() {
    if (stack.empty()) {
        std::cerr << "Error: not enough tokens." << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string tok = stack.top();
    stack.pop();

    if (isNumber(tok))
        return std::atof(tok.c_str());

    if (isOperator(tok)) {
        double b = compute();
        double a = compute();
        return applyOperator(tok[0], a, b);
    }

    std::cerr << "Error: invalid token '" << tok << "'." << std::endl;
    std::exit(EXIT_FAILURE);
    return 0;
}

void RPNCalculator::setExpression(const std::string &expr) {
    expression = expr;
}

double RPNCalculator::evaluate() {
    tokenize();
    double result = compute();

    if (!stack.empty()) {
        std::cerr << "Error: malformed expression. Remaining tokens = "
                  << stack.size() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return result;
}
