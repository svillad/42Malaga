#ifndef DEQUE_SORTER_HPP
#define DEQUE_SORTER_HPP

#include <deque>

class DequeSorter {
public:
    // Constructor por defecto.
    DequeSorter();

    // Constructor que recibe un std::deque<int>.
    DequeSorter(const std::deque<int>& numbers);

    // Constructor de copia.
    DequeSorter(const DequeSorter &other);

    // Operador de asignación.
    DequeSorter &operator=(const DequeSorter &other);

    // Destructor.
    ~DequeSorter();

    // Devuelve el contenedor interno (ordenado después de sort()).
    const std::deque<int>& getNumbers() const;

    // Ordena el contenedor usando Ford–Johnson con secuencia de Jacobsthal.
    void sort();

    // Calcula el orden de inserción para 'm' elementos perdedores basándose en la secuencia de Jacobsthal.
    std::deque<int> computeInsertionOrder(int m) const;

    // Calcula el n-ésimo número de Jacobsthal.
    int jacobsthal(int n) const;

    // Inserción binaria: inserta 'value' en 'deq' (que se asume ordenado).
    static void binaryInsert(std::deque<int>& deq, int value);

    // Función principal del algoritmo Ford–Johnson (versión simplificada con Jacobsthal) para std::deque.
    void fordJohnsonSort(std::deque<int>& deq);

private:
    std::deque<int> numbers_;

    // Métodos auxiliares privados (estáticos) para modularizar la función.

    // Separa el contenedor 'deq' (con tamaño par) en winners y losers.
    static void splitIntoPairs(const std::deque<int>& deq,
                               std::deque<int>& winners,
                               std::deque<int>& losers);

    // Inserta en 'winners' los elementos de 'losers' cuyos índices no estén en 'insertionOrder'.
    static void insertRemainingLosers(const std::deque<int>& losers,
                                        const std::deque<int>& insertionOrder,
                                        std::deque<int>& winners);
};

#endif // DEQUE_SORTER_HPP
