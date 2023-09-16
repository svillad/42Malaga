/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:36:24 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 12:45:19 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIZE 4
#define OK 0
#define ERROR 1

int	ft_put_c(char A[][6], int x, int y, char c)
{
	if (A[x][y] != '*' && A[x][y] != c)
		return (ERROR);
	A[x][y] = c;
	return (OK);
}

int	ft_check_rule_1(char A[][6])
{
	int	pos;
	int	error;

	pos = 1;
	error = 0;
	while (pos <= SIZE && error == 0)
	{
		error = 0;
		if (A[pos][0] == '1')
			error += ft_put_c(A, pos, 1, '4');
		if (A[0][pos] == '1')
			error += ft_put_c(A, 1, pos, '4');
		if (A[pos][5] == '1')
			error += ft_put_c(A, pos, 4, '4');
		if (A[5][pos] == '1')
			error += ft_put_c(A, 4, pos, '4');
		pos++;
	}
	return (error);
}
