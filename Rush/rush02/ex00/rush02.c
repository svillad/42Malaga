/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:21:04 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/23 23:07:31 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"

int	low_div(int num, t_number *dictionary)
{
	int	i;
	int	lowest_div;

	i = -1;
	while (dictionary[++i].num != -1)
		if ((num > dictionary[i].num) && (lowest_div < dictionary[i].num))
			lowest_div = dictionary[i].num;
	return (lowest_div);
}

void	algorithm(int num, t_number *dictionary, int first, int div)
{
	if (num == 100 || num == 1000 || num == 1000000 || num == 1000000000)
		ft_putstr("one ");
	if ((ft_find_number(dictionary, num) && first)
		|| (ft_find_number(dictionary, num) && !first && num != 0))
		ft_putstr(ft_find_number(dictionary, num));
	else if (num > 20 && num < 100)
	{
		ft_putstr(ft_find_number(dictionary, num - (num % 10)));
		ft_putstr("-");
		ft_putstr(ft_find_number(dictionary, num % 10));
	}
	else
	{
		div = low_div(num, dictionary);
		if (div != 0)
		{
			algorithm(num / div, dictionary, 0, div);
			ft_putchar(' ');
			ft_putstr(ft_find_number(dictionary, div));
			if (num % div != 0)
				ft_putchar(' ');
			algorithm(num % div, dictionary, 0, div);
		}
	}
}
