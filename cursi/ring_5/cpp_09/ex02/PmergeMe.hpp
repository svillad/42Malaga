#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>

class PmergeMe {
private:
    std::vector<int> vectorNumbers;
    std::deque<int> dequeNumbers;

    bool isValidNumber(const std::string &s) const;
    void fordJohnsonSort(std::vector<int>& vec);
    void fordJohnsonSort(std::deque<int>& deq);
    
    void createPairs(std::vector<int>& arr, std::vector<int>& P, std::vector<int>& S);
    void insertSecondary(std::vector<int>& P, std::vector<int>& S);
    std::vector<int> generateJacobsthalSequence(int n);

    void createPairs(std::deque<int>& arr, std::deque<int>& P, std::deque<int>& S);
    void insertSecondary(std::deque<int>& P, std::deque<int>& S);
    std::deque<int> generateJacobsthalSequence(int n, int flag);

public:
    PmergeMe();
    PmergeMe(int argc, char** argv);
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();
    
    void parseInput(int argc, char** argv);
   
    const std::vector<int>& getVectorNumbers() const;
    void setNumbers(const std::vector<int>& numbers);
    void sortVector();
    void mergeInsertionSort(std::vector<int>& arr);

    const std::deque<int>& getDequeNumbers() const;
    void setNumbers(const std::deque<int>& numbers);
    void sortDeque();
    void mergeInsertionSort(std::deque<int>& arr);
};

#endif
