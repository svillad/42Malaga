#include <stdio.h>
#include <string.h>
#include "../libft.h"

// Función de prueba personalizada
void test_ft_memcmp() {
    printf("\n****************************************\n");
    printf("TEST: ft_memcmp\n");
    int total = 0;
    int ok = 0;

    // Caso 1
    total++;
    const char *text1 = "salut";
    const char *text2 = "salut";
    int ft_result = ft_memcmp(text1, text2, 5);
    int std_result = memcmp(text1, text2, 5);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%s) ft_memcmp:%c no coincide con memcmp:%c.\n",
        total, text1, text2, ft_result, std_result);
    } else {
        ok++;
    }

    // Caso 2
   total++;
    const char *text3 = "t\200";
    const char *text4 = "t\0";
    ft_result = ft_memcmp(text3, text4, 2);
    std_result = memcmp(text3, text4, 2);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%s) ft_memcmp:%c no coincide con memcmp:%c.\n",
        total, text3, text4, ft_result, std_result);
    } else {
        ok++;
    }

    // Caso 3
    total++;
    const char *text5 = "testss";
    const char *text6 = "test";
    ft_result = ft_memcmp(text5, text6, 5);
    std_result = memcmp(text5, text6, 5);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%s) ft_memcmp:%c no coincide con memcmp:%c.\n",
        total, text5, text6, ft_result, std_result);
    } else {
        ok++;
    }

    // Caso 4
    total++;
    const char *text7 = "abcdefghij";
    const char *text8 = "abcdefgxyz";
    ft_result = ft_memcmp(text7, text8, 3);
    std_result = memcmp(text7, text8, 3);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%s) ft_memcmp:%c no coincide con memcmp:%c.\n",
        total, text7, text8, ft_result, std_result);
    } else {
        ok++;
    }

    // Caso 5
    total++;
    const char *text9 = "abcdefghij";
    const char *text0 = "abcdefgxyz";
    ft_result = ft_memcmp(text9, text0, 0);
    std_result = memcmp(text9, text0, 0);
    if (ft_result != std_result) {
        printf("  %d) Error: (%s,%s) ft_memcmp:%c no coincide con memcmp:%c.\n",
        total, text9, text0, ft_result, std_result);
    } else {
        ok++;
    }

    printf("\n -> porcentaje correcto: %d/%d", ok, total);
    printf("\n----------------------------------------\n");
}