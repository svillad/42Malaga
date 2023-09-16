/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ten_queens_puzzle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:57:48 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/20 17:04:46 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#define N 10

void	ft_get_queens_positions(int table[][N], char queens[]);
void	ft_init_table(int table[][N]);
int		ft_is_good_position(int table[][N], int row, int col);
int		ft_ten_queens_puzzle(void);

void	ft_get_queens_positions(int table[][N], char queens[])
{
	int	i;
	int	j;
	int	p;

	i = -1;
	p = 0;
	while (++i < N)
	{
		j = -1;
		while (++j < N)
		{
			if (table[i][j] == 1)
			{
				queens[p++] = j + '0';
				break ;
			}
		}
	}
	queens[p++] = '\n';
	queens[p] = '\0';
}

void	ft_init_table(int table[][N])
{
	int	i;
	int	j;

	i = -1;
	while (++i < N)
	{
		j = -1;
		while (++j < N)
			table[i][j] = 0;
	}
}

int	ft_is_good_position(int table[][N], int row, int col)
{
	int	i;
	int	j;

	i = -1;
	while (++i < row)
	{
		if (table[i][col] == 1)
			return (0);
	}
	i = row + 1;
	j = col + 1;
	while (--i >= 0 && --j >= 0)
	{
		if (table[i][j] == 1)
			return (0);
	}
	i = row + 1;
	j = col - 1;
	while (--i >= 0 && ++j < N)
	{
		if (table[i][j] == 1)
			return (0);
	}
	return (1);
}

int	ft_set_queens(int table[][N], int row)
{
	int		col;
	int		solutions;
	char	queens[N + 2];

	if (row == N)
	{
		ft_get_queens_positions(table, queens);
		write(1, queens, N + 1);
		return (1);
	}
	solutions = 0;
	col = -1;
	while (++col < N)
	{
		if (ft_is_good_position(table, row, col))
		{
			table[row][col] = 1;
			solutions += ft_set_queens(table, row + 1);
			table[row][col] = 0;
		}
	}
	return (solutions);
}

int	ft_ten_queens_puzzle(void)
{
	int	table[N][N];
	int	solutions; 

	ft_init_table(table);
	solutions = ft_set_queens(table, 0);
	return (solutions);
}
