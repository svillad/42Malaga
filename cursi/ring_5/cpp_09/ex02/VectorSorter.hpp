#ifndef VECTOR_SORTER_HPP
#define VECTOR_SORTER_HPP

#include <vector>

class VectorSorter {
public:
    // Constructor por defecto.
    VectorSorter();

    // Constructor que recibe un vector de enteros.
    VectorSorter(const std::vector<int>& numbers);

    // Constructor de copia.
    VectorSorter(const VectorSorter &other);

    // Operador de asignación.
    VectorSorter &operator=(const VectorSorter &other);

    // Destructor.
    ~VectorSorter();

    // Devuelve el vector ordenado.
    const std::vector<int>& getNumbers() const;

    // Ordena el vector usando Ford–Johnson con secuencia de Jacobsthal.
    void sort();

private:
    std::vector<int> numbers_;

    // Implementación recursiva del algoritmo Ford–Johnson.
    void fordJohnsonSort(std::vector<int>& vec);

    // Inserción binaria: inserta 'value' en 'vec' (ya ordenado) usando búsqueda binaria.
    void binaryInsert(std::vector<int>& vec, int value);

    // Calcula el n-ésimo número de Jacobsthal.
    int jacobsthal(int n) const;

    // Calcula el orden de inserción para 'm' elementos perdedores usando la secuencia de Jacobsthal.
    std::vector<int> computeInsertionOrder(int m) const;
};

#endif // VECTOR_SORTER_HPP
