#ifndef DEQUE_SORTER_HPP
#define DEQUE_SORTER_HPP

#include <deque>

class DequeSorter {
private:
    std::deque<int> numbers_;

    static void splitIntoPairs(const std::deque<int>& deq,
                               std::deque<int>& winners,
                               std::deque<int>& losers);
    static void insertRemainingLosers(const std::deque<int>& losers,
                                        const std::deque<int>& insertionOrder,
                                        std::deque<int>& winners);
public:
    DequeSorter();
    DequeSorter(const std::deque<int>& numbers);
    DequeSorter(const DequeSorter &other);
    DequeSorter &operator=(const DequeSorter &other);
    ~DequeSorter();

    const std::deque<int>& getNumbers() const;
    void sort();
    std::deque<int> computeInsertionOrder(int m) const;
    int jacobsthal(int n) const;
    static void binaryInsert(std::deque<int>& deq, int value);
    void fordJohnsonSort(std::deque<int>& deq);


};

#endif
