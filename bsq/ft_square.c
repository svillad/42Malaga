/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_square.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:19:25 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:19:27 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_square.h"

void	ft_put_square(char **map, int *square, char *line1)
{
	int	i;
	int	j;
	int	n;
	int	nx;

	n = ft_strlen(line1);
	i = square[0];
	j = square[1];
	nx = square[2];
	while (i < (square[0] + nx))
	{
		map[i][j] = line1[n - 1];
		j++;
		if (j == (square[1] + nx))
		{
			i++;
			j = j - nx;
		}
	}
}

int	*ft_find_max_square(int **smap, int rows, int cols)
{
	int	i;
	int	j;
	int	*square;

	square = (int *)malloc(3 * sizeof(int));
	if (!square)
		return (NULL);
	i = -1;
	square[2] = smap[0][0];
	while (++i < rows)
	{
		j = -1;
		while (++j < cols)
		{
			if (smap[i][j] > square[2])
			{
				square[0] = i;
				square[1] = j;
				square[2] = smap[i][j];
			}
		}
	}
	square[0] = square[0] - square[2] + 1;
	square[1] = square[1] - square[2] + 1;
	return (square);
}
