/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:27:35 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 08:58:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	fill_center(char mat[][6], char c)
{
	int		contx;
	int		conty;
	int		arrcont;

	conty = 0;
	arrcont = 0;
	while (conty < 6)
	{	
		contx = 0;
		while (contx < 6)
		{	
			mat[contx][conty] = c;
			contx++;
		}
		conty++;
	}
}

void	matrix_filler(char mat[][6], char c, char ls[])
{
	int		arrcont;

	arrcont = 0;
	fill_center(mat, c);
	while (arrcont < 16)
	{
		if (arrcont < 4)
		{
			mat[arrcont + 1][0] = ls[arrcont];
		}
		if (arrcont > 3 && arrcont < 8)
		{
			mat[arrcont - 3][5] = ls[arrcont];
		}
		if (arrcont > 7 && arrcont < 12)
		{
			mat[0][arrcont - 7] = ls[arrcont];
		}
		if (arrcont > 11 && arrcont < 16)
		{
			mat[5][arrcont - 11] = ls[arrcont];
		}
		arrcont++;
	}
}

void	matrix_shower(char mat[][6])
{
	int		contx;
	int		conty;

	conty = 0;
	contx = 0;
	while (conty < 6)
	{	
		contx = 0;
		while (contx < 6)
		{	
			write(1, &mat[contx][conty], 1);
			contx++;
		}
		write (1, "\n", 1);
		conty++;
	}
}

void	result_shower(char mat[][6])
{
	int		contx;
	int		conty;

	conty = 1;
	contx = 1;
	while (conty < 5)
	{	
		contx = 1;
		while (contx < 5)
		{	
			write(1, &mat[contx][conty], 1);
			if (contx != 4)
				write(1, " ", 1);
			contx++;
		}
		write (1, "\n", 1);
		conty++;
	}
}
