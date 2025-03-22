#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <algorithm>

PmergeMe::PmergeMe() : numbers() { }

PmergeMe::PmergeMe(int argc, char** argv) : numbers() {
    parseInput(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe &other) : numbers(other.numbers) { }

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        numbers = other.numbers;
    }
    return *this;
}

PmergeMe::~PmergeMe() { }

bool PmergeMe::isValidNumber(const std::string &s) const {
    if (s.empty())
        return false;
    for (size_t i = 0; i < s.size(); ++i) {
        if (!std::isdigit(s[i]))
            return false;
    }
    return true;
}

void PmergeMe::parseInput(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (!isValidNumber(arg)) {
            std::cerr << "Error: invalid input '" << arg 
                      << "'. Only positive integers are allowed." << std::endl;
            std::cerr << "----------------------------------------------\n" << std::endl;
            exit(1);
        }
        int num = std::atoi(arg.c_str());
        if (num <= 0) {
            std::cerr << "Error: input must be a positive integer in valid range: '" 
                      << arg << "'" << std::endl;
            std::cerr << "----------------------------------------------\n" << std::endl;
            exit(1);
        }
        if (std::find(numbers.begin(), numbers.end(), num) != numbers.end()) {
            std::cerr << "Error: duplicate input '" << num << "'." << std::endl;
            std::cerr << "----------------------------------------------\n" << std::endl;
            exit(1);
        }
        numbers.push_back(num);
    }
}


const std::vector<int>& PmergeMe::getNumbers() const {
    return numbers;
}
