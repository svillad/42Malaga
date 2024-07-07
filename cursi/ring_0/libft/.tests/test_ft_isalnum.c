#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_isalnum() {
    printf("\n****************************************\n");
    printf("TEST: ft_isalnum\n");
    int total = 0;
    int ok = 0;

    // Prueba caracteres alfanuméricos
    char T1[] = {'a', 'A', 'z', 'Z', '0', '9'};
    for (size_t i = 0; i < sizeof(T1) / sizeof(T1[0]); i++) {
        total++;
        if (ft_isalnum(T1[i]) != isalnum(T1[i])) {
            printf("  %d) Error: ft_isalnum('%c') no coincide con isalnum('%c').\n", total, T1[i], T1[i]);
        }else {
            ok++;
        }
    }

    // Prueba caracteres no alfanuméricos
    char T2[] = {'$', ' ', '\n', '\t'};
    for (size_t i = 0; i < sizeof(T2) / sizeof(T2[0]); i++) {
        total++;
        if (ft_isalnum(T2[i]) != isalnum(T2[i])) {
            printf("  %d) Error: ft_isalnum('%c') no coincide con isalnum('%c').\n", total, T2[i], T2[i]);
        }else {
            ok++;
        }
    }

    printf("\n  -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
