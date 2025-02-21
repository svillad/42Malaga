#ifndef RPNCALCULATOR_HPP
#define RPNCALCULATOR_HPP

#include <string>
#include <vector>

class RPNCalculator {
public:
    // Constructor por defecto
    RPNCalculator();

    // Constructor que recibe la expresión RPN.
    RPNCalculator(const std::string &expression);

    // Constructor de copia.
    RPNCalculator(const RPNCalculator &other);

    // Operador de asignación.
    RPNCalculator &operator=(const RPNCalculator &other);

    // Destructor.
    ~RPNCalculator();

    // Devuelve el vector de tokens.
    const std::vector<std::string>& getTokens() const;

    // Imprime los tokens en pantalla.
    void printTokens() const;

    // Evalúa la expresión RPN y devuelve el resultado.
    double evaluate() const;

private:
    std::string expression_;
    std::vector<std::string> tokens_;

    // Tokeniza la expresión.
    void tokenize();

    // Determina si el token es un operador.
    bool isOperator(const std::string &token) const;

    // Aplica el operador a dos operandos.
    double applyOperator(char op, double a, double b) const;

    // Determina si el token es un número válido.
    bool isNumber(const std::string &token) const;
};

#endif // RPNCALCULATOR_HPP
