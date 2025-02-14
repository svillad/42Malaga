#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <cstdlib>
#include <stdexcept>

template <typename T>
class Array {
private:
    T*           _data; 
    unsigned int _size;

public:
    Array();
    Array(unsigned int n);
    Array(unsigned int n, const T* values);
    Array(unsigned int n, const Array<T>& other);
    Array(const Array& other);
    Array& operator=(const Array& other);
    ~Array();

    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;

    unsigned int size() const;
};

#include "Array.tpp"

#endif
