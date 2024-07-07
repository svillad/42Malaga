#include <stdio.h>
#include <string.h> 
#include "../libft.h"

// Función de prueba personalizada
void test_ft_strrchr() {
    printf("\n****************************************\n");
    printf("TEST: ft_strrchr\n");
    int total = 0;
    int ok = 0;

    // Caso 1: Cadena vacía, buscar '\0'
    total++;
    const char *empty_str = "";
    int search_char = '\0';
    char *ft_result = ft_strrchr(empty_str, search_char);
    char *std_result = strrchr(empty_str, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strch:%c no coincide con strrchr:%c.\n",
        total, empty_str, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 2: Cadena no vacía, multiples \0
    total++;
    const char *text2 = "there is so \0ma\0ny \0 \\0 in t\0his stri\0ng !\0\0\0\0";
    search_char = 'a';
    ft_result = ft_strrchr(text2, search_char);
    std_result = strrchr(text2, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strch:%s no coincide con strrchr:%s.\n",
        total, text2, search_char, ft_result, std_result);
    } else {
        ok++;
    }

    // Caso 3: Cadena no vacía, buscar carácter en medio
    total++;
    const char *text = "Hola, mundo!";
    search_char = 'a';
    ft_result = ft_strrchr(text, search_char);
    std_result = strrchr(text, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strch:%c no coincide con strrchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 4: Cadena no vacía, buscar carácter en el extremo
    total++;
    search_char = '!';
    ft_result = ft_strrchr(text, search_char);
    std_result = strrchr(text, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strch:%c no coincide con strrchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 5: Carácter no encontrado
    total++;
    search_char = 'x';
    ft_result = ft_strrchr(text, search_char);
    std_result = strrchr(text, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strch:%c no coincide con strrchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
