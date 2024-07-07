#include <stdio.h>
#include <string.h> 
#include "../libft.h"

// Función de prueba personalizada
void test_ft_strlen() {
    printf("\n****************************************\n");
    printf("TEST: ft_strlen\n");
    int total = 0;
    int ok = 0;

    const char *text = "Hola, mundo!";
    size_t ft_length = ft_strlen(text);
    size_t std_length = strlen(text);

    total++;
    if (ft_length != std_length) {
        printf("  %d) Error: ft_strlen('%s')=%lu no coincide con strlen('%s')=%lu.\n",
        total, text, ft_length, text, std_length);
    } else {
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
