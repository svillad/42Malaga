/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_serie4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:35:30 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 12:46:19 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIZE 4
#define OK 0
#define ERROR 1

int	ft_put_serie_in_x(char A[][6], int y, char serie[])
{
	int	i;
	int	x;

	i = 0;
	x = 1;
	while (serie[i])
	{
		if (A[x][y] != '*' && A[x][y] != serie[i])
			return (ERROR);
		A[x][y] = serie[i];
		x++;
		i++;
	}
	return (OK);
}

int	ft_put_serie_in_y(char A[][6], int x, char serie[])
{
	int	i;
	int	y;

	i = 0;
	y = 1;
	while (serie[i])
	{
		if (A[x][y] != '*' && A[x][y] != serie[i])
			return (ERROR);
		A[x][y] = serie[i];
		y++;
		i++;
	}
	return (OK);
}

int	ft_check_rule_serie_4(char A[][6])
{
	int	pos;
	int	error;

	pos = 1;
	error = 0;
	while (pos <= SIZE && error == 0)
	{
		error = 0;
		if (A[pos][0] == '4')
			error += ft_put_serie_in_y(A, pos, "1234");
		if (A[0][pos] == '4')
			error += ft_put_serie_in_x(A, pos, "1234");
		if (A[pos][5] == '4')
			error += ft_put_serie_in_y(A, pos, "4321");
		if (A[5][pos] == '4')
			error += ft_put_serie_in_x(A, pos, "4321");
		pos++;
	}
	return (error);
}
