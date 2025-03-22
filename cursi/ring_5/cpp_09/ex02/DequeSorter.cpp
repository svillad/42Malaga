#include "DequeSorter.hpp"
#include <deque>
#include <cstdlib>
#include <iostream>
#include <algorithm>

DequeSorter::DequeSorter() : numbers() {
}

DequeSorter::DequeSorter(const std::deque<int>& numbers) : numbers(numbers) {
}

DequeSorter::DequeSorter(const DequeSorter &other) : numbers(other.numbers) {
}

DequeSorter &DequeSorter::operator=(const DequeSorter &other) {
    if (this != &other) {
        numbers = other.numbers;
    }
    return *this;
}

DequeSorter::~DequeSorter() {
}

const std::deque<int>& DequeSorter::getNumbers() const {
    return numbers;
}

void DequeSorter::setNumbers(const std::deque<int>& numbers) {
    this->numbers = numbers;
}

void DequeSorter::sort() {
    if (!numbers.empty()) {
        fordJohnsonSort(numbers);
    }
}

void DequeSorter::fordJohnsonSort(std::deque<int>& deq) {
    if (deq.size() <= 1) return;

    std::deque<int> sorted;
    std::deque<int> waiting;

    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        if (deq[i] > deq[i + 1])
            std::swap(deq[i], deq[i + 1]);
        sorted.push_back(deq[i + 1]);
        waiting.push_back(deq[i]);
    }
    if (deq.size() % 2 != 0)
        sorted.push_back(deq.back());
    std::sort(sorted.begin(), sorted.end());

    for (size_t i = 0; i < waiting.size(); ++i) {
        std::deque<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), waiting[i]);
        sorted.insert(pos, waiting[i]);
    }
    deq = sorted;
}
