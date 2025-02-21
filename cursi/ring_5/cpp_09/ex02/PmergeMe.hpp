#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <string>

class PmergeMe {
public:
    // Constructor por defecto.
    PmergeMe();

    // Constructor que parsea la entrada de la línea de comandos.
    PmergeMe(int argc, char** argv);

    // Constructor de copia.
    PmergeMe(const PmergeMe &other);

    // Operador de asignación.
    PmergeMe &operator=(const PmergeMe &other);

    // Destructor.
    ~PmergeMe();

    // Retorna el vector de números parseados.
    const std::vector<int>& getNumbers() const;

private:
    std::vector<int> numbers_;

    // Función auxiliar que valida que una cadena sea un entero positivo.
    bool isValidNumber(const std::string &s) const;

    // Función que parsea los argumentos de entrada.
    void parseInput(int argc, char** argv);
};

#endif // PMERGEME_HPP
