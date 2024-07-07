#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_tolower() {
    printf("\n****************************************\n");
    printf("TEST: ft_tolower\n");
    int total = 0;
    int ok = 0;

    // Caracteres en minúsculas
    for (char c = 'A'; c <= 'Z'; c++) {
        total++;
        if (ft_tolower(c) != tolower(c)) {
            printf("  %d) Error: ft_tolower('%c') no coincide con tolower('%c').\n", total, c, c);
        } else {
            ok++;
        }
    }

    // Caracteres en mayúsculas y otros caracteres
    char T[] = {'a', 'b', 'c', '1', '@', '\n', '\t'};
    for (size_t i = 0; i < sizeof(T) / sizeof(T[0]); i++) {
        total++;
        if (ft_tolower(T[i]) != tolower(T[i])) {
            printf("  %d)Error: ft_tolower('%c') no coincide con tolower('%c').\n", total, T[i], T[i]);
        } else {
            ok++;
        }
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
