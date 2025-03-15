#include "VectorSorter.hpp"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using std::vector;
using std::swap;

VectorSorter::VectorSorter() : numbers() {
}

VectorSorter::VectorSorter(const vector<int>& numbers) : numbers(numbers) {
}

VectorSorter::VectorSorter(const VectorSorter &other) : numbers(other.numbers) {
}

VectorSorter &VectorSorter::operator=(const VectorSorter &other) {
    if (this != &other) {
        numbers = other.numbers;
    }
    return *this;
}

VectorSorter::~VectorSorter() {
}

const vector<int>& VectorSorter::getNumbers() const {
    return numbers;
}

void VectorSorter::sort() {
    if (!numbers.empty()) {
        fordJohnsonSort(numbers);
    }
}

void VectorSorter::binaryInsert(vector<int>& vec, int value) {
    int left = 0, right = vec.size();
    while (left < right) {
        int mid = (left + right) / 2;
        if (vec[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    vec.insert(vec.begin() + left, value);
}

// Calculates the n-th Jacobsthal number.
// J(0) = 0, J(1) = 1, and for n >= 2, J(n) = J(n-1) + 2*J(n-2)
int VectorSorter::jacobsthal(int n) const {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = b + 2 * a;
        a = b;
        b = c;
    }
    return b;
}

vector<int> VectorSorter::computeInsertionOrder(int m) const {
    vector<int> order;
    if (m <= 0)
        return order;
    // Siempre se inserta primero el perdedor del primer par (índice 0).
    order.push_back(0);
    int j = 2;
    while (true) {
        int J = jacobsthal(j);
        if (J >= m)
            break;
        order.push_back(J);
        j++;
    }
    // Añadimos los índices restantes que no hayan sido incluidos, en orden creciente.
    for (int i = 0; i < m; ++i) {
        if (std::find(order.begin(), order.end(), i) == order.end())
            order.push_back(i);
    }
    return order;
}


// Función principal del algoritmo Ford–Johnson (versión simplificada con Jacobsthal).
void VectorSorter::fordJohnsonSort(vector<int>& vec) {
    int n = vec.size();
    if (n < 2)
        return;
    if (n == 2) {
        if (vec[0] > vec[1])
            swap(vec[0], vec[1]);
        return;
    }

    bool odd = false;
    int extra;
    if (n % 2 == 1) {
        odd = true;
        extra = vec.back();
        vec.pop_back();
        n--;
    }

    vector<int> winners;
    vector<int> losers;
    // Formar pares: para cada par, el menor se coloca en winners y el mayor en losers.
    for (int i = 0; i < n; i += 2) {
        if (vec[i] < vec[i+1]) {
            winners.push_back(vec[i]);
            losers.push_back(vec[i+1]);
        } else {
            winners.push_back(vec[i+1]);
            losers.push_back(vec[i]);
        }
    }

    // Ordenar recursivamente los ganadores.
    fordJohnsonSort(winners);

    // Calcular el orden de inserción de los perdedores usando la secuencia de Jacobsthal.
    vector<int> insertionOrder = computeInsertionOrder(losers.size());

    // Insertar los perdedores en la cadena de ganadores siguiendo el orden determinado.
    for (size_t k = 0; k < insertionOrder.size(); ++k) {
        size_t idx = insertionOrder[k];
        if (idx < losers.size()) {
            binaryInsert(winners, losers[idx]);
        }
    }

    // En caso de que existan perdedores que no se hayan insertado (por si acaso),
    // los insertamos en el orden natural.
    for (size_t i = 0; i < losers.size(); ++i) {
        bool alreadyInserted = false;
        for (size_t k = 0; k < insertionOrder.size(); ++k) {
            if (insertionOrder[k] == static_cast<int>(i)) {
                alreadyInserted = true;
                break;
            }
        }
        if (!alreadyInserted) {
            binaryInsert(winners, losers[i]);
        }
    }

    // Si había un elemento extra, se inserta también.
    if (odd) {
        binaryInsert(winners, extra);
    }

    vec = winners;
}
