#include "Span.hpp"

Span::Span(unsigned int N) : capacity(N) {
}

Span::Span(Span const &other)
    : capacity(other.capacity), numbers(other.numbers) {
}

Span &Span::operator=(Span const &other) {
    if (this != &other) {
        capacity = other.capacity;
        numbers  = other.numbers;
    }
    return *this;
}

Span::~Span() {
}

void Span::addNumber(int value)
{
    if (numbers.size() >= capacity)
        throw std::runtime_error("Span is already full. Cannot add more numbers.");
    numbers.push_back(value);
}

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>

int Span::shortestSpan() const
{
    if (numbers.size() < 2)
        throw std::runtime_error("Not enough elements in Span to compute a span.");

    std::vector<int> tmp(numbers);
    std::sort(tmp.begin(), tmp.end());
    std::vector<int> diffs(tmp.size() - 1);
    std::transform(tmp.begin() + 1, tmp.end(), tmp.begin(), diffs.begin(), std::minus<int>());
    return *std::min_element(diffs.begin(), diffs.end());
}


int Span::longestSpan() const
{
    if (numbers.size() < 2)
        throw std::runtime_error("Not enough elements in Span to compute a span.");

    int minVal = *std::min_element(numbers.begin(), numbers.end());
    int maxVal = *std::max_element(numbers.begin(), numbers.end());
    return maxVal - minVal;
}
