#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <algorithm>

PmergeMe::PmergeMe() : numbers_() { }

PmergeMe::PmergeMe(int argc, char** argv) : numbers_() {
    parseInput(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe &other) : numbers_(other.numbers_) { }

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        numbers_ = other.numbers_;
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
            std::cerr << "Error: input must be a positive integer: '" 
                      << arg << "'" << std::endl;
            std::cerr << "----------------------------------------------\n" << std::endl;
            exit(1);
        }
        if (std::find(numbers_.begin(), numbers_.end(), num) != numbers_.end()) {
            std::cerr << "Error: duplicate input '" << num << "'." << std::endl;
            std::cerr << "----------------------------------------------\n" << std::endl;
            exit(1);
        }
        numbers_.push_back(num);
    }
}


const std::vector<int>& PmergeMe::getNumbers() const {
    return numbers_;
}
