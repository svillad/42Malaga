#include <stdio.h>
#include <ctype.h>
#include "../../libft/libft.h"

// Función de prueba personalizada
void test_ft_isalpha() {
    printf("\n****************************************\n");
    printf("TEST: ft_isalpha\n");
    int ok = 0;

    // Prueba caracteres válidos ('a', 'A', 'z', 'Z')
    if (ft_isalpha('a') != isalpha('a')) {
        printf("Error: 'a' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('A') != isalpha('A')) {
        printf("Error: 'A' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('z') != isalpha('z')) {
        printf("Error: 'z' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('Z') != isalpha('Z')) {
        printf("Error: 'Z' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    // Prueba caracteres inválidos (números, símbolos, espacios, etc.)
    if (ft_isalpha('1') != isalpha('1')) {
        printf("Error: '1' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha('$') != isalpha('$')) {
        printf("Error: '$' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    if (ft_isalpha(' ') != isalpha(' ')) {
        printf("Error: ' ' no coincide con isalpha.\n");
    } else{
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/7", ok);
    printf("\n----------------------------------------\n");
}
