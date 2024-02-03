#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Número total de argumentos: %d\n", argc);

    for (int i = 0; i < argc; i++) {
        printf("Argumentos %d: %s\n", i, argv[i]);
    }

    return 0;
}