#include "VectorSorter.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

VectorSorter::VectorSorter() : numbers() {
}

VectorSorter::VectorSorter(const std::vector<int>& numbers) : numbers(numbers) {
}

VectorSorter::VectorSorter(const VectorSorter &other) : numbers(other.numbers) {
}

VectorSorter &VectorSorter::operator=(const VectorSorter &other) {
    if (this != &other) {
        numbers = other.numbers;
    }
    return *this;
}

VectorSorter::~VectorSorter() {
}

const std::vector<int>& VectorSorter::getNumbers() const {
    return numbers;
}

void VectorSorter::setNumbers(const std::vector<int>& numbers) {
    this->numbers = numbers;
}

void VectorSorter::sort() {
    if (!numbers.empty()) {
        fordJohnsonSort(numbers);
    }
}

void VectorSorter::fordJohnsonSort(std::vector<int>& vec) {
    if (vec.size() <= 1) return;

    std::vector<int> sorted;
    std::vector<int> waiting;

    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (vec[i] > vec[i + 1])
            std::swap(vec[i], vec[i + 1]);
        sorted.push_back(vec[i + 1]);
        waiting.push_back(vec[i]);
    }
    if (vec.size() % 2 != 0)
        sorted.push_back(vec.back());
    std::sort(sorted.begin(), sorted.end());

    for (size_t i = 0; i < waiting.size(); ++i) {
        std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), waiting[i]);
        sorted.insert(pos, waiting[i]);
    }
    vec = sorted;
}
