#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_isascii() {
    printf("\n****************************************\n");
    printf("TEST: ft_isascii\n");
    int total = 0;
    int ok = 0;

    // Caracteres dentro del rango ASCII (0-127)
    for (int i = 0; i <= 127; i++) {
        total++;
        if (ft_isascii(i) != isascii(i)) {
            printf("  %d) Error: ft_isascii(%d) no coincide con isascii('%d').\n", total, i, i);
        } else {
            ok++;
        }
    }

    // Caracteres fuera del rango ASCII (128-255)
    for (int i = 128; i <= 255; i++) {
        total++;
        if (ft_isascii(i) != isascii(i)) {
            printf("  %d) Error: ft_isascii('%d') no coincide con isascii('%d').\n", total, i, i);
        } else {
            ok++;
        }
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
