/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rule_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:35:28 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 12:45:43 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define SIZE 4
#define OK 0
#define ERROR 1

int	ft_put_c(char A[][6], int x, int y, char c);
int	ft_put_serie_in_x(char A[][6], int y, char serie[]);
int	ft_put_serie_in_y(char A[][6], int x, char serie[]);

int	ft_check_rule_32_put_4(char A[][6], int pos)
{
	int	error;

	error = 0;
	if (A[pos][0] == '3' && A[pos][5] == '2')
		error += ft_put_c(A, pos, 3, '4');
	if (A[0][pos] == '3' && A[5][pos] == '2')
		error += ft_put_c(A, 3, pos, '4');
	if (A[pos][5] == '3' && A[pos][0] == '2')
		error += ft_put_c(A, pos, 2, '4');
	if (A[5][pos] == '3' && A[0][pos] == '2')
		error += ft_put_c(A, 2, pos, '4');
	return (error);
}

int	ft_check_rule_32_put_serie(char A[][6], int pos)
{
	int	error;

	error = 0;
	if (A[pos][0] == '3' && A[pos][5] == '2' && A[pos][1] == '2')
		error += ft_put_serie_in_y(A, pos, "2341");
	if (A[0][pos] == '3' && A[5][pos] == '2' && A[1][pos] == '2')
		error += ft_put_serie_in_x(A, pos, "2341");
	if (A[pos][5] == '3' && A[pos][0] == '2' && A[pos][4] == '2')
		error += ft_put_serie_in_y(A, pos, "1432");
	if (A[5][pos] == '3' && A[0][pos] == '2' && A[4][pos] == '2')
		error += ft_put_serie_in_x(A, pos, "1432");
	return (error);
}

int	ft_check_rule_32(char A[][6])
{
	int	pos;
	int	error;

	pos = 1;
	error = 0;
	while (pos <= SIZE && error == 0)
	{
		error = 0;
		error += ft_check_rule_32_put_4(A, pos);
		error += ft_check_rule_32_put_serie(A, pos);
		pos++;
	}
	return (error);
}
