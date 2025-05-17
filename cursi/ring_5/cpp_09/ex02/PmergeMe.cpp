#include "PmergeMe.hpp"
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <algorithm>

void print(std::vector<int> vectorNumbers){
    for (size_t i = 0; i < vectorNumbers.size(); ++i) {
        std::cout << vectorNumbers[i] << " ";
    }
    std::cout << std::endl;
}

void print(std::deque<int> vectorNumbers){
    for (size_t i = 0; i < vectorNumbers.size(); ++i) {
        std::cout << vectorNumbers[i] << " ";
    }
    std::cout << std::endl;
}

PmergeMe::PmergeMe() : vectorNumbers(), dequeNumbers() { }

PmergeMe::PmergeMe(int argc, char** argv) : vectorNumbers(), dequeNumbers() {
    parseInput(argc, argv);
}

PmergeMe::PmergeMe(const PmergeMe &other)
    : vectorNumbers(other.vectorNumbers), dequeNumbers(other.dequeNumbers) {
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other) {
    if (this != &other) {
        vectorNumbers = other.vectorNumbers;
        dequeNumbers = other.dequeNumbers;
    }
    return *this;
}

PmergeMe::~PmergeMe() { }

bool PmergeMe::isValidNumber(const std::string &s) const {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void PmergeMe::parseInput(int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (!isValidNumber(arg))
            throw std::invalid_argument("Error: invalid input '" + arg + "'. Only positive integers are allowed.");

        int num = std::atoi(arg.c_str());
        if (num <= 0)
            throw std::out_of_range("Error: input must be a positive integer in valid range: '" + arg + "'");

        if (std::find(vectorNumbers.begin(), vectorNumbers.end(), num) != vectorNumbers.end())
            throw std::runtime_error("Error: duplicate input '" + std::to_string(num) + "'.");

        vectorNumbers.push_back(num);
        dequeNumbers.push_back(num);
    }
}

const std::vector<int>& PmergeMe::getVectorNumbers() const {
    return vectorNumbers;
}

const std::deque<int>& PmergeMe::getDequeNumbers() const {
    return dequeNumbers;
}

void PmergeMe::setNumbers(const std::vector<int>& numbers) {
    vectorNumbers = numbers;
    dequeNumbers = std::deque<int>(numbers.begin(), numbers.end());
}

void PmergeMe::setNumbers(const std::deque<int>& numbers) {
    dequeNumbers = numbers;
    vectorNumbers = std::vector<int>(numbers.begin(), numbers.end());
}

void PmergeMe::sortVector() {
    if (!vectorNumbers.empty()) {
        mergeInsertionSort(vectorNumbers);
    }
}

void PmergeMe::sortDeque() {
    if (!dequeNumbers.empty()) {
        mergeInsertionSort(dequeNumbers);
    }
}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec) {
    if (vec.size() <= 1) return;
    std::vector<int> sorted, waiting;
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (vec[i] > vec[i + 1]) std::swap(vec[i], vec[i + 1]);
        sorted.push_back(vec[i + 1]);
        waiting.push_back(vec[i]);
    }
    if (vec.size() % 2 != 0) sorted.push_back(vec.back());
    std::sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i < waiting.size(); ++i) {
        std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), waiting[i]);
        sorted.insert(pos, waiting[i]);
    }
    vec = sorted;
}

void PmergeMe::fordJohnsonSort(std::deque<int>& deq) {
    if (deq.size() <= 1) return;
    std::deque<int> sorted, waiting;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        if (deq[i] > deq[i + 1]) std::swap(deq[i], deq[i + 1]);
        sorted.push_back(deq[i + 1]);
        waiting.push_back(deq[i]);
    }
    if (deq.size() % 2 != 0) sorted.push_back(deq.back());
    std::sort(sorted.begin(), sorted.end());
    for (size_t i = 0; i < waiting.size(); ++i) {
        std::deque<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), waiting[i]);
        sorted.insert(pos, waiting[i]);
    }
    deq = sorted;
}

void PmergeMe::mergeInsertionSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;

    std::vector<int> P, S;
    createPairs(arr, P, S);
    mergeInsertionSort(P);
    insertSecondary(P, S);
    arr = P;
}

void PmergeMe::createPairs(std::vector<int>& arr, std::vector<int>& P, std::vector<int>& S) {
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);
        
        S.push_back(arr[i]);
        P.push_back(arr[i + 1]);
    }

    if (arr.size() % 2 != 0) {
        P.push_back(arr.back());
    }
}

void PmergeMe::insertSecondary(std::vector<int>& P, std::vector<int>& S) {
    if (S.empty()) return;

    std::vector<int> J = generateJacobsthalSequence(S.size());
    std::vector<bool> inserted(S.size(), false);

    for (size_t j = 0; j < J.size(); ++j) {
        size_t index = J[j];
        if (index >= S.size()) break;

        int value = S[index];
        std::vector<int>::iterator it = P.begin();
        while (it != P.end() && *it < value) ++it;
        P.insert(it, value);

        inserted[index] = true;
    }

    for (size_t i = 0; i < S.size(); ++i) {
        if (!inserted[i]) {
            int value = S[i];
            std::vector<int>::iterator it = P.begin();
            while (it != P.end() && *it < value) ++it;
            P.insert(it, value);
        }
    }
}

std::vector<int> PmergeMe::generateJacobsthalSequence(int n) {
    std::vector<int> sequence;
    int j0 = 0;
    int j1 = 1;

    sequence.push_back(0);
    while ((int)sequence.size() < n && j1 < n) {
        int jNext = j1 + 2 * j0;
        j0 = j1;
        j1 = jNext;
        if (j1 < n)
            sequence.push_back(j1);
        
        int val = j1 - 1;
        bool exists = std::find(sequence.begin(), sequence.end(), val) != sequence.end();
        while (!exists && val >= 0) {
            sequence.push_back(val--);
            exists = std::find(sequence.begin(), sequence.end(), val) != sequence.end();
        }
    }

    return sequence;
}



void PmergeMe::mergeInsertionSort(std::deque<int>& arr) {
    if (arr.size() <= 1) return;

    std::deque<int> P, S;
    createPairs(arr, P, S);
    mergeInsertionSort(P);
    insertSecondary(P, S);
    arr = P;
}

void PmergeMe::createPairs(std::deque<int>& arr, std::deque<int>& P, std::deque<int>& S) {
    for (size_t i = 0; i + 1 < arr.size(); i += 2) {
        if (arr[i] > arr[i + 1])
            std::swap(arr[i], arr[i + 1]);

        S.push_back(arr[i]);
        P.push_back(arr[i + 1]);
    }

    if (arr.size() % 2 != 0) {
        P.push_back(arr.back());
    }
}

void PmergeMe::insertSecondary(std::deque<int>& P, std::deque<int>& S) {
    if (S.empty()) return;

    std::deque<int> J = generateJacobsthalSequence(S.size(), 0);
    std::vector<bool> inserted(S.size(), false);

    for (size_t j = 0; j < J.size(); ++j) {
        size_t index = J[j];
        if (index >= S.size()) break;

        int value = S[index];
        std::deque<int>::iterator it = P.begin();
        while (it != P.end() && *it < value) ++it;
        P.insert(it, value);

        inserted[index] = true;
    }

    for (size_t i = 0; i < S.size(); ++i) {
        if (!inserted[i]) {
            int value = S[i];
            std::deque<int>::iterator it = P.begin();
            while (it != P.end() && *it < value) ++it;
            P.insert(it, value);
        }
    }
}

std::deque<int> PmergeMe::generateJacobsthalSequence(int n, int flag) {
    (void) flag;
    std::deque<int> sequence;
    int j0 = 0;
    int j1 = 1;

    sequence.push_back(0);
    while ((int)sequence.size() < n && j1 < n) {
        int jNext = j1 + 2 * j0;
        j0 = j1;
        j1 = jNext;
        if (j1 < n)
            sequence.push_back(j1);

        int val = j1 - 1;
        bool exists = std::find(sequence.begin(), sequence.end(), val) != sequence.end();
        while (!exists && val >= 0) {
            sequence.push_back(val--);
            exists = std::find(sequence.begin(), sequence.end(), val) != sequence.end();
        }
    }

    return sequence;
}
