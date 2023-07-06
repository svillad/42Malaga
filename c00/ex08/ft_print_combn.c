/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 01:26:08 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/07 01:28:59 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_combn_recursive(int n, int start, int current, int *buffer)
{
	int		i;
	char	digit;

	if (current == n)
	{
		i = 0;
		while (i < n)
		{
			digit = buffer[i] + '0';
			write(1, &digit, 1);
			i++;
		}
		if (buffer[0] != 10 - n)
		{
			write(1, ", ", 2);
		}
		return ;
	}
	i = start;
	while (i < 10)
	{
		buffer[current] = i;
		ft_print_combn_recursive(n, i + 1, current + 1, buffer);
		i++;
	}
}

void	ft_print_combn(int n)
{
	int	buffer[n];

	ft_print_combn_recursive(n, 0, 0, buffer);
	write(1, "\n", 1);
}
