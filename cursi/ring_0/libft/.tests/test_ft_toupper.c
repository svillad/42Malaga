#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_toupper() {
    printf("\n****************************************\n");
    printf("TEST: ft_toupper\n");
    int total = 0;
    int ok = 0;

    // Caracteres en minúsculas
    for (char c = 'a'; c <= 'z'; c++) {
        total++;
        if (ft_toupper(c) != toupper(c)) {
            printf("  %d) Error: ft_toupper('%c') no coincide con toupper('%c').\n", total, c, c);
        } else {
            ok++;
        }
    }

    // Caracteres en mayúsculas y otros caracteres
    char T[] = {'A', 'B', 'C', '1', '@', '\n', '\t'};
    for (size_t i = 0; i < sizeof(T) / sizeof(T[0]); i++) {
        total++;
        if (ft_toupper(T[i]) != toupper(T[i])) {
            printf("  %d)Error: ft_toupper('%c') no coincide con toupper('%c').\n", total, T[i], T[i]);
        } else {
            ok++;
        }
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
