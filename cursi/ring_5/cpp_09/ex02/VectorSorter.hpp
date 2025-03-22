#ifndef VECTOR_SORTER_HPP
#define VECTOR_SORTER_HPP

#include <vector>

class VectorSorter {
private:
    std::vector<int> numbers;
    void fordJohnsonSort(std::vector<int>& vec);

public:
    VectorSorter();
    VectorSorter(const std::vector<int>& numbers);
    VectorSorter(const VectorSorter &other);
    VectorSorter &operator=(const VectorSorter &other);
    ~VectorSorter();

    const std::vector<int>& getNumbers() const;
    void setNumbers(const std::vector<int>& numbers);
    
    void sort();
};

#endif
