#include "PmergeMe.hpp"
#include "VectorSorter.hpp"
#include "DequeSorter.hpp"
#include <iostream>
#include <ctime>
#include <vector>
#include <deque>
#include <sstream>
#include <iomanip>
#include <string>

template <typename Container>
void printContainer(const Container& container) {
    const size_t size = container.size();
    if (size > 20) {
        for (size_t i = 0; i < 10; ++i) {
            std::cout << container[i] << " ";
        }
        std::cout << "[...] " << container[size - 2] << " " << container[size - 1];
    } else {
        for (size_t i = 0; i < size; ++i) {
            std::cout << container[i] << " ";
        }
    }
    std::cout << std::endl;
}

std::string formatTime(double timeUs) {
    std::ostringstream oss;
    if (timeUs < 1000.0) {
        oss << std::fixed << std::setprecision(2) << timeUs << " us";
    } else if (timeUs < 1000000.0) {
        double timeMs = timeUs / 1000.0;
        oss << std::fixed << std::setprecision(2) << timeMs << " ms";
    } else {
        double timeS = timeUs / 1000000.0;
        oss << std::fixed << std::setprecision(2) << timeS << " s";
    }
    return oss.str();
}

double measureParserTime(PmergeMe &parser, int argc, char** argv) {
    std::clock_t start = std::clock();
    parser.parseInput(argc, argv);
    std::clock_t end = std::clock();
    return 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

double measureVectorSortTime(VectorSorter &sorter, const std::vector<int>& num) {
    std::clock_t start = std::clock();
    std::vector<int> numbers = num;
    sorter.setNumbers(numbers);
    sorter.sort();
    std::clock_t end = std::clock();
    return 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

double measureDequeSortTime(DequeSorter &sorter, const std::vector<int>& num) {
    std::clock_t start = std::clock();
    std::deque<int> deq(num.begin(), num.end());
    sorter.setNumbers(deq);
    sorter.sort();
    std::clock_t end = std::clock();
    return 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " number1 number2 ..." << std::endl;
        std::cerr << "----------------------------------------------\n" << std::endl;
        return 1;
    }

    PmergeMe parser;
    VectorSorter vectorSorter;
    DequeSorter dequeSorter;

    double parseTime  = measureParserTime(parser, argc, argv);
    double vectorTime = parseTime + measureVectorSortTime(vectorSorter, parser.getNumbers());
    double dequeTime  = parseTime + measureDequeSortTime(dequeSorter, parser.getNumbers());

    std::cout << "Before: ";
    printContainer(parser.getNumbers());
    std::cout << "After:  ";
    printContainer(vectorSorter.getNumbers());
    std::cout << "Time to process a range of " << parser.getNumbers().size() 
              << " elements with std::vector : " << formatTime(vectorTime) << std::endl;
    std::cout << "Time to process a range of " << parser.getNumbers().size() 
              << " elements with std::deque  : " << formatTime(dequeTime) << std::endl;
    std::cout << "----------------------------------------------\n" << std::endl;

    return 0;
}
