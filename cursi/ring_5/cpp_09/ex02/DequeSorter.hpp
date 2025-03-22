#ifndef DEQUE_SORTER_HPP
#define DEQUE_SORTER_HPP

#include <deque>

class DequeSorter {
private:
    std::deque<int> numbers;
    void fordJohnsonSort(std::deque<int>& deq);

public:
    DequeSorter();
    DequeSorter(const std::deque<int>& numbers);
    DequeSorter(const DequeSorter &other);
    DequeSorter &operator=(const DequeSorter &other);
    ~DequeSorter();

    const std::deque<int>& getNumbers() const;
    void setNumbers(const std::deque<int>& numbers);
    
    void sort();
};

#endif
