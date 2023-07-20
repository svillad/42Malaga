#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define N 4

char  *ft_get_queens_positions(int **table);
int	**ft_init_table(int n);
int ft_is_good_position(int **table, int fila, int col);
int ft_ten_queens_puzzle(void);

char  *ft_get_queens_positions(int **table)
{
	int		i;
	int		j;
	int 	p;
	char	*queens;

	queens = (char *)malloc ((N+2) * sizeof(char));
	i = -1;
	p = 0;
	while (++i < N)
	{
		j = -1;
		while (++j < N)
		{
			if (table[i][j] == 1)
			{
				queens[p] = j + '0';
				p++;
				break ;
			}
		}	
	}
	queens[p++] = '\n';
	queens[p] = '\0';
	return queens;
}

void ft_print_table(int **table) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c ", table[i][j] == 1 ? 'Q' : '-');
		}
		printf("\n");
	}
	printf("\n");
}

int	**ft_init_table(int n)
{
	int	i;
	int	j;
	int	**table;

	table = (int **)malloc (n * sizeof(int *));
	i = -1;
	while (++i < N)
	{
		table[i] = (int *)malloc(n * sizeof(int));
		j = -1;
		while (++j < N)
			table[i][j] = 0;
	}
	return table;
}

int ft_is_good_position(int **table, int fila, int col)
{
	int	i;
	int	j;

	i = -1;
	while (++i < fila) {
		if (table[i][col] == 1)
			return (0);
	}
	i = fila + 1;
	j = col + 1;
	while (--i >= 0 && --j >= 0) {
		if (table[i][j] == 1)
			return (0);			
	}
	i = fila + 1;
	j = col - 1;
	while (--i >= 0 && ++j < N) {
		if (table[i][j] == 1)
			return (0);
	}
	return (1);
}

int ft_set_queens(int **table, int fila) {
	int		col;
	int		soluciones;
	char	*queens;
	char	c;

	if (fila == N){
		// ft_print_table(table);
		queens = ft_get_queens_positions(table);
		write(1, queens, N+1);
		// scanf("%c", &c);
		free(queens);
		return (1);
	}

	soluciones = 0;
	col = -1;
	while (++col < N) {
		ft_print_table(table);
		scanf("%c", &c);

		if (ft_is_good_position(table, fila, col)) {
			table[fila][col] = 1;
			soluciones += ft_set_queens(table, fila + 1);
			table[fila][col] = 0;
		}
	}
	return soluciones;
}

int ft_ten_queens_puzzle(void) {
	int		**table;
	int		soluciones; 

	table = ft_init_table(N);
	// ft_print_table(table);
	soluciones = ft_set_queens(table, 0);
	//soluciones = ft_ten_queens_puzzle();
	printf("Total de soluciones encontradas: %d\n", soluciones);
	free(table);
	return soluciones;
}

int main (void)
{
	int	s;

	s = ft_ten_queens_puzzle();
	printf("Total de soluciones encontradas: %d\n", s);
	return (0);
}
