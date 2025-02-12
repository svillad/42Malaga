#ifndef ITER_HPP
#define ITER_HPP

#include <iostream>

template <typename T, typename F>
void iter(T* array, size_t length, F func) {
    for (size_t i = 0; i < length; ++i) {
        func(array[i]);
    }
}

template <typename T>
void iter(T* array, size_t length, void (*func)(const T&)) {
    for (size_t i = 0; i < length; ++i) {
        func(array[i]);
    }
}

template <typename T>
void printElement(const T& value) {
    std::cout << value << " ";
}

template <typename T>
void incrementElement(T& value) {
    value += 1;
}

template <typename T>
void doubleElement(T& value) {
    value *= 2;
}

#endif
