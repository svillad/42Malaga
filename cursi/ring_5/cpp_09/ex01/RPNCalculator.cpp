#include "RPNCalculator.hpp"
#include <sstream>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <cctype>

RPNCalculator::RPNCalculator() : expression(""), tokens() {
}

RPNCalculator::RPNCalculator(const std::string &expression)
    : expression(expression), tokens() {
    tokenize();
}

RPNCalculator::RPNCalculator(const RPNCalculator &other)
    : expression(other.expression), tokens(other.tokens) {
}

RPNCalculator &RPNCalculator::operator=(const RPNCalculator &other) {
    if (this != &other) {
        expression = other.expression;
        tokens = other.tokens;
    }
    return *this;
}

RPNCalculator::~RPNCalculator() {
}

const std::vector<std::string>& RPNCalculator::getTokens() const {
    return tokens;
}

void RPNCalculator::printTokens() const {
    std::cout << "Tokens:" << std::endl;
    for (size_t i = 0; i < tokens.size(); ++i) {
        std::cout << tokens[i] << std::endl;
    }
}

void RPNCalculator::tokenize() {
    std::istringstream iss(expression);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
}

bool RPNCalculator::isOperator(const std::string &token) const {
    return token.size() == 1 &&
           (token[0] == '+' || token[0] == '-' ||
            token[0] == '*' || token[0] == '/');
}

double RPNCalculator::applyOperator(char op, double a, double b) const {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                std::cerr << "Error: division by zero." << std::endl;
                exit(1);
            }
            return a / b;
        default:
            std::cerr << "Error: unknown operator '" << op << "'." << std::endl;
            exit(1);
    }
}

bool RPNCalculator::isNumber(const std::string &token) const {
    std::istringstream iss(token);
    double d;
    iss >> d;
    return !token.empty() && iss.eof() && !iss.fail();
}

double RPNCalculator::evaluate() const {
    std::stack<double> s;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string &token = tokens[i];
        if (isOperator(token)) {
            if (s.size() < 2) {
                std::cerr << "Error: not enough operands for operator '"
                          << token << "'." << std::endl;
                exit(1);
            }
            double b = s.top(); s.pop();
            double a = s.top(); s.pop();
            double result = applyOperator(token[0], a, b);
            s.push(result);
        } else if (isNumber(token)) {
            double num = std::atof(token.c_str());
            s.push(num);
        } else {
            std::cerr << "Error: invalid token '" << token << "'." << std::endl;
            exit(1);
        }
    }
    if (s.size() != 1) {
        std::cerr << "Error: malformed expression. Stack size: "
                  << s.size() << std::endl;
        exit(1);
    }
    return s.top();
}
