/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simolina <simolina@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 12:23:45 by simolina          #+#    #+#             */
/*   Updated: 2023/07/16 12:39:09 by simolina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	sub_check3y5(char mat[][6])
{
	int	result;
	int	pos;
	int	aux;

	result = 0;
	pos = 1;
	while (pos < 5 && result == 0)
	{	
		aux = mat[pos][0] - '0' + mat[pos][5] - '0';
		if (aux < 3 || aux > 5)
			result = 1;
		pos++;
	}
	pos = 1;
	while (pos < 5 && result == 0)
	{	
		aux = mat[0][pos] - '0' + mat[5][pos] - '0';
		if (aux < 3 || aux > 5)
			result = 1;
		pos++;
	}
	return (result);
}
