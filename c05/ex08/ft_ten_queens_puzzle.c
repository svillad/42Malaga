#include <stdio.h>

#define N 8

int tablero[N][N];

void imprimirTablero() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c ", tablero[i][j] == 1 ? 'Q' : '.');
		}
		printf("\n");
	}
	printf("\n");
}

int esSeguro(int fila, int columna) {
	int	i;
	int	j;
	char c;
	scanf("%c",&c);
	printf("\n");

	imprimirTablero();

	printf("(%d, %d)\n", fila, columna);
	
	i = -1;
	while (++i < fila) {
		printf("  1) (%d, %d) ", i, columna);
		if (tablero[i][columna] == 1)
			return 0;
	}
	i = fila + 1;
	j = columna + 1;
	while (--i >= 0 && --j >= 0) {
		printf("  2) (%d, %d) ", i, j);
		if (tablero[i][j] == 1)
			return 0;			
	}
	i = fila + 1;
	j = columna - 1;
	while (--i >= 0 && ++j < N) {
		printf("  3) (%d, %d) ", i, j);
		if (tablero[i][j] == 1)
			return 0;
	}
	return (1);
}

int resolverNReinas(int fila) {
	char c;
	if (fila == N) {
		imprimirTablero();
		return 1;
	}

	int soluciones = 0;

	for (int columna = 0; columna < N; columna++) {
		if (esSeguro(fila, columna)) {
			tablero[fila][columna] = 1;
			soluciones += resolverNReinas(fila + 1);
			tablero[fila][columna] = 0;
		}
	}


	return soluciones;
}

int ft_ten_queens_puzzle(void);

int ft_ten_queens_puzzle(void) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			tablero[i][j] = 0;
		}
	}

	int totalSoluciones = resolverNReinas(0);
	printf("Total de soluciones encontradas: %d\n", totalSoluciones);

	return 0;
}

int main (void)
{
	ft_ten_queens_puzzle();
	return (0);
}
