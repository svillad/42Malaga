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

// Función para medir el tiempo de ordenación de un VectorSorter.
// Retorna el tiempo en microsegundos.
double measureVectorSortTime(VectorSorter& sorter) {
    std::clock_t start = std::clock();
    sorter.sort();
    std::clock_t end = std::clock();
    return 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

// Función para medir el tiempo de ordenación de un DequeSorter.
// Retorna el tiempo en microsegundos.
double measureDequeSortTime(DequeSorter& sorter) {
    std::clock_t start = std::clock();
    sorter.sort();
    std::clock_t end = std::clock();
    return 1000000.0 * (end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char** argv) {
    std::cout << "[main] New program execution" << std::endl;
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " number1 number2 ..." << std::endl;
        std::cerr << "----------------------------------------------\n" << std::endl;
        return 1;
    }

    // Paso 1: Parseo y validación de entrada.
    PmergeMe parser(argc, argv);
    const std::vector<int>& numbers = parser.getNumbers();

    // Imprimir la secuencia original.
    std::cout << "Before: ";
    printContainer(numbers);

    // Paso 2: Inicialización para std::vector.
    VectorSorter vectorSorter(numbers);
    // Paso 3: Inicialización para std::deque.
    std::deque<int> deq(numbers.begin(), numbers.end());
    DequeSorter dequeSorter(deq);

    // Medir el tiempo de ordenación para std::vector.
    double vectorTime = measureVectorSortTime(vectorSorter);
    // Medir el tiempo de ordenación para std::deque.
    double dequeTime = measureDequeSortTime(dequeSorter);

    // Imprimir la secuencia ordenada para std::vector.
    std::cout << "After (std::vector): ";
    printContainer(vectorSorter.getNumbers());
    // Imprimir la secuencia ordenada para std::deque.
    std::cout << "After (std::deque): ";
    printContainer(dequeSorter.getNumbers());

    // Mostrar los tiempos de procesamiento.
    std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::vector : " << formatTime(vectorTime) << std::endl;
    std::cout << "Time to process a range of " << numbers.size() 
              << " elements with std::deque : " << formatTime(dequeTime) << std::endl;
    std::cout << "----------------------------------------------\n" << std::endl;

    return 0;
}
