#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <string>

class PmergeMe {
private:
    std::vector<int> numbers;

    bool isValidNumber(const std::string &s) const;

public:
    PmergeMe();
    PmergeMe(int argc, char** argv);
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    const std::vector<int>& getNumbers() const;
    void parseInput(int argc, char** argv);
};

#endif
