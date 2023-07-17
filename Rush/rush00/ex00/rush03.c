/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzurera- <mzurera-@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:40:29 by mzurera-          #+#    #+#             */
/*   Updated: 2023/07/08 15:40:35 by mzurera-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

void	check_position(int i, int j, int x, int y)
{
	if (j == 0 && (i == 0 || i == y - 1))
	{
		ft_putchar('A');
	}
	else if (j == x - 1 && (i == 0 || i == y - 1))
	{
		ft_putchar('C');
	}
	else if (i == 0 || j == 0 || i == y - 1 || j == x - 1)
	{
		ft_putchar('B');
	}
	else
	{
		ft_putchar(' ');
	}
}

void	rush(int x, int y)
{
	int	i;
	int	j;

	if (x <= 0 || y <= 0)
		return ;
	i = 0;
	while (i < y)
	{
		j = 0;
		while (j < x)
		{
			check_position(i, j, x, y);
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}
