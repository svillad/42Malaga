#ifndef SPAN_TPP
#define SPAN_TPP

#include "Span.hpp"
#include <algorithm>
#include <iterator>

template <typename InputIterator>
void Span::addNumber(InputIterator first, InputIterator last)
{
    unsigned int dist = static_cast<unsigned int>(std::distance(first, last));
    if (numbers.size() + dist > capacity)
        throw std::runtime_error("Not enough capacity in Span to add the range of numbers.");
    numbers.insert(numbers.end(), first, last);
}

#endif
