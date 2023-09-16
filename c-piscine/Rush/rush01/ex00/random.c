/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:19:06 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 14:39:22 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		ft_char_in_str(char c, const char *str);

void	ft_get_numbers_in_row(char A[][6], int row, char *serie)
{
	int	x;
	int	i;

	x = 1;
	i = 0;
	while (x <= 4)
	{
		if (A[x][row] != '*')
			serie[i++] = A[x][row];
		x++;
	}
	serie[i] = '\0';
}

void	ft_get_numbers_in_col(char A[][6], int col, char *serie)
{
	int	y;
	int	i;

	y = 1;
	i = 0;
	while (y <= 4)
	{
		if (A[col][y] != '*')
			serie[i++] = A[col][y];
		y++;
	}
	serie[i] = '\0';
}

void	ft_add_random_c(char A[][6], int x, int y, int ex)
{
	const char	serie[][4] = {"1234", "2134", "3124", "1324"};
	int			i;
	char		used_x[5];
	char		used_y[5];

	i = 0;
	ft_get_numbers_in_row(A, y, used_x);
	ft_get_numbers_in_col(A, x, used_y);
	while (serie[ex / 4][(i + ex) % 4])
	{
		if (!ft_char_in_str(serie[ex / 4][(i + ex) % 4], used_x)
			&& !ft_char_in_str(serie[ex / 4][(i + ex) % 4], used_y))
		{
			A[x][y] = serie[ex / 4][(i + ex) % 4];
			return ;
		}
		i++;
	}
}

void	ft_random_filler(char A[][6], int ex)
{
	int			x;
	int			y;

	y = 1;
	while (y <= 4)
	{
		x = 1;
		while (x <= 4)
		{
			if (A[x][y] == '*')
				ft_add_random_c(A, x, y, ex);
			x++;
		}
		y++;
	}
}
