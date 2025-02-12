#include "Array.hpp"

template <typename T>
Array<T>::Array() : _data(NULL), _size(0) {
}

template <typename T>
Array<T>::Array(unsigned int n) : _size(n) {
    _data = new T[n]();
}

template <typename T>
Array<T>::Array(unsigned int n, const T* values) : _size(n) {
    _data = new T[n]();
    for (unsigned int i = 0; i < n; i++) {
        _data[i] = values[i];
    }
}

template <typename T>
Array<T>::Array(unsigned int n, const Array<T>& other) : _size(n) {
    _data = new T[_size];
    unsigned int limit = (other.size() < _size) ? other.size() : _size;
    for (unsigned int i = 0; i < limit; i++) {
        _data[i] = other[i];
    }
}

template <typename T>
Array<T>::Array(const Array& other) : _size(other._size) {
    _data = new T[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        delete[] _data;

        _size = other._size;
        _data = new T[_size];
        for (unsigned int i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template <typename T>
Array<T>::~Array() {
    delete[] _data;
}

template <typename T>
T& Array<T>::operator[](unsigned int index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of bounds");
    }
    return _data[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of bounds");
    }
    return _data[index];
}

template <typename T>
unsigned int Array<T>::size() const {
    return _size;
}