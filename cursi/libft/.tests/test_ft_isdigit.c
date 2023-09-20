#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_isdigit() {
    printf("\n****************************************\n");
    printf("TEST: ft_isdigit\n");
    int total = 0;
    int ok = 0;

    // Prueba dígitos válidos ('0' - '9')
    for (char c = '0'; c <= '9'; c++) {
        total++;
        if (ft_isdigit(c) != isdigit(c)) {
            printf("  %d) Error: ft_isdigit('%c'):%d no coincide con isdigit('%c'):%d.\n",
            total, c, ft_isdigit(c), c, isdigit(c));
        } else {
            ok++;
        }
    }

    // Prueba caracteres no dígitos
    char T[] = {'a', 'A', '$', ' ', '\n', '\t'};
    for (size_t i = 0; i < sizeof(T) / sizeof(T[0]); i++) {
        total++;
        if (ft_isdigit(T[i]) != isdigit(T[i])) {
            printf("  %d) Error: ft_isdigit('%c'):%d  no coincide con isdigit('%c'):%d.\n",
            total, T[i], ft_isdigit(T[i]), T[i], ft_isdigit(T[i]));
        } else {
            ok++;
        }
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
