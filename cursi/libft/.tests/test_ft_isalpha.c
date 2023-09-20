#include <stdio.h>
#include <ctype.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_isalpha() {
    printf("\n****************************************\n");
    printf("TEST: ft_isalpha\n");
    int ok = 0;

    // Prueba caracteres válidos ('a', 'A', 'z', 'Z')
    if (ft_isalpha('a') != isalpha('a')) {
        printf("  1) Error: 'a' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('A') != isalpha('A')) {
        printf("  2) Error: 'A' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('z') != isalpha('z')) {
        printf("  3) Error: 'z' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('Z') != isalpha('Z')) {
        printf("  4) Error: 'Z' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    // Prueba caracteres inválidos (números, símbolos, espacios, etc.)
    if (ft_isalpha('1') != isalpha('1')) {
        printf("  5) Error: '1' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('$') != isalpha('$')) {
        printf("  6) Error: '$' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha(' ') != isalpha(' ')) {
        printf("  7) Error: ' ' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/7", ok);
    printf("\n----------------------------------------\n");
}
