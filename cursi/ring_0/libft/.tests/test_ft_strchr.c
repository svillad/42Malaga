#include <stdio.h>
#include <string.h> 
#include "../libft.h"

// Función de prueba personalizada
void test_ft_strchr() {
    printf("\n****************************************\n");
    printf("TEST: ft_strchr\n");
    int total = 0;
    int ok = 0;

    // Caso 1: Cadena vacía, buscar '\0'
    total++;
    const char *empty_str = "";
    int search_char = '\0';
    char *ft_result = ft_strchr(empty_str, search_char);
    char *std_result = strchr(empty_str, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strchr:%c no coincide con strchr:%c.\n",
        total, empty_str, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 2: Cadena no vacía, buscar carácter en medio
    total++;
    const char *text = "Hola, mundo!";
    search_char = 'a';
    ft_result = ft_strchr(text, search_char);
    std_result = strchr(text, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strchr:%c no coincide con strchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 3: Cadena no vacía, buscar carácter en el extremo
    total++;
    search_char = '!';
    ft_result = ft_strchr(text, search_char);
    std_result = strchr(text, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strchr:%c no coincide con strchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    // Caso 4: Carácter no encontrado
    total++;
    search_char = 'x';
    ft_result = ft_strchr(text, search_char);
    std_result = strchr(text, search_char);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%c) ft_strchr:%c no coincide con strchr:%c.\n",
        total, text, search_char, *ft_result, *std_result);
    } else {
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}
