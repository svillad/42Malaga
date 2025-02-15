#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <stdexcept>

class Span
{
private:
    unsigned int      capacity;
    std::vector<int>  numbers;

    Span();

public:
    explicit Span(unsigned int N);
    Span(Span const &other);
    Span &operator=(Span const &other);
    ~Span();

    void addNumber(int value);
    template <typename InputIterator>
    void addNumber(InputIterator first, InputIterator last);

    int shortestSpan() const;
    int longestSpan() const;
};

#include "Span.tpp"

#endif
