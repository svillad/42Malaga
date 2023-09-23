#include <stdio.h>
#include <string.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_memchr() {
    printf("\n****************************************\n");
    printf("TEST: ft_memchr\n");
    int total = 0;
    int ok = 0;

    // Caso 1: Cadena vacía, buscar '\0'
    total++;
    const char *empty_str = "";
    int search_char = '\0';
    char *ft_result = ft_memchr(empty_str, search_char, 3);
    char *std_result = memchr(empty_str, search_char, 3);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_memchr:%c no coincide con memchr:%c.\n",
        total, empty_str, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 2: Cadena no vacía, buscar carácter en medio
    total++;
    const char *text = "Hola, mundo!";
    search_char = 'a';
    ft_result = ft_memchr(text, search_char, 4);
    std_result = memchr(text, search_char, 4);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_memchr:%c no coincide con memchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 3: Cadena no vacía, buscar carácter en el extremo
    total++;
    search_char = '!';
    ft_result = ft_memchr(text, search_char, 4);
    std_result = memchr(text, search_char, 4);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_memchr:%c no coincide con memchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 4: Carácter no encontrado
    total++;
    search_char = 'x';
    ft_result = ft_memchr(text, search_char, 20);
    std_result = memchr(text, search_char, 20);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_memchr:%c no coincide con memchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}