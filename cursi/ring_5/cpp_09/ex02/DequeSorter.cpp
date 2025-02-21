#include "DequeSorter.hpp"
#include <deque>
#include <cstdlib>
#include <iostream>
#include <algorithm> // Para std::min, std::max, std::swap, std::find

using std::deque;
using std::swap;

//--------------------------------------------
// Constructores, Operador de Asignación y Destructor
//--------------------------------------------

DequeSorter::DequeSorter() : numbers_() { }

DequeSorter::DequeSorter(const deque<int>& numbers) : numbers_(numbers) { }

DequeSorter::DequeSorter(const DequeSorter &other) : numbers_(other.numbers_) { }

DequeSorter &DequeSorter::operator=(const DequeSorter &other) {
    if (this != &other) {
        numbers_ = other.numbers_;
    }
    return *this;
}

DequeSorter::~DequeSorter() { }

const deque<int>& DequeSorter::getNumbers() const {
    return numbers_;
}

void DequeSorter::sort() {
    if (!numbers_.empty()) {
        fordJohnsonSort(numbers_);
    }
}

//--------------------------------------------
// Métodos Auxiliares Convertidos en Miembros Estáticos
//--------------------------------------------

// Separa el contenedor 'deq' (con tamaño par) en winners y losers.
// winners: contiene el mínimo de cada par.
// losers: contiene el máximo de cada par.
void DequeSorter::splitIntoPairs(const deque<int>& deq,
                                 deque<int>& winners,
                                 deque<int>& losers) {
    for (size_t i = 0; i < deq.size(); i += 2) {
        winners.push_back(std::min(deq[i], deq[i+1]));
        losers.push_back(std::max(deq[i], deq[i+1]));
    }
}

// Inserta en 'winners' los elementos de 'losers' cuyos índices no estén en 'insertionOrder'.
// Se utiliza std::find para comprobar si un índice ya fue incluido.
void DequeSorter::insertRemainingLosers(const deque<int>& losers,
                                          const deque<int>& insertionOrder,
                                          deque<int>& winners) {
    for (size_t i = 0; i < losers.size(); ++i) {
        if (std::find(insertionOrder.begin(), insertionOrder.end(), i) == insertionOrder.end()) {
            binaryInsert(winners, losers[i]);
        }
    }
}

//--------------------------------------------
// Otras Funciones Miembro
//--------------------------------------------

// Inserción binaria: inserta 'value' en 'deq', que se asume ordenado.
void DequeSorter::binaryInsert(deque<int>& deq, int value) {
    int left = 0, right = deq.size();
    while (left < right) {
        int mid = (left + right) / 2;
        if (deq[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    deq.insert(deq.begin() + left, value);
}

// Calcula el n-ésimo número de Jacobsthal.
// J(0)=0, J(1)=1, y para n>=2: J(n)=J(n-1) + 2*J(n-2)
int DequeSorter::jacobsthal(int n) const {
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

// Calcula el orden de inserción para 'm' perdedores basándose en la secuencia de Jacobsthal.
deque<int> DequeSorter::computeInsertionOrder(int m) const {
    deque<int> order;
    if (m <= 0)
        return order;
    // Se inserta primero el perdedor del primer par (índice 0).
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

//--------------------------------------------
// Función Principal del Algoritmo Ford–Johnson (Versión Simplificada con Jacobsthal) para std::deque
//--------------------------------------------
void DequeSorter::fordJohnsonSort(deque<int>& deq) {
    int n = deq.size();
    if (n < 2)
        return;
    if (n == 2) {
        if (deq[0] > deq[1])
            swap(deq[0], deq[1]);
        return;
    }

    // Si el número de elementos es impar, se extrae el último para procesarlo al final.
    bool odd = false;
    int extra = 0;
    if (n % 2 == 1) {
        odd = true;
        extra = deq.back();
        deq.pop_back();
        n--;
    }

    deque<int> winners;
    deque<int> losers;
    // Formar pares: para cada par, el menor se coloca en winners y el mayor en losers.
    splitIntoPairs(deq, winners, losers);

    // Ordenar recursivamente los winners.
    fordJohnsonSort(winners);

    // Calcular el orden de inserción de los losers usando la secuencia de Jacobsthal.
    deque<int> insertionOrder = computeInsertionOrder(losers.size());

    // Insertar los losers en winners siguiendo el orden determinado.
    for (size_t k = 0; k < insertionOrder.size(); ++k) {
        size_t idx = insertionOrder[k];
        if (idx < losers.size()) {
            binaryInsert(winners, losers[idx]);
        }
    }

    // Insertar los losers restantes que no fueron incluidos en el orden.
    insertRemainingLosers(losers, insertionOrder, winners);

    // Si había un elemento extra, se inserta también.
    if (odd) {
        binaryInsert(winners, extra);
    }

    deq = winners;
}
