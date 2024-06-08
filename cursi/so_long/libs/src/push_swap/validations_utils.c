/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:07:59 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/13 16:54:33 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	are_digits(const char *str)
{
	int	i;
	int	is_negative;
	int	is_positive;

	i = -1;
	while (str[++i])
	{
		is_negative = str[i] == '-';
		is_positive = str[i] == '+';
		if (i < (int)ft_strlen(str) - 1)
		{
			is_negative *= ft_isdigit(str[i + 1]);
			is_positive *= ft_isdigit(str[i + 1]);
		}
		if (i > 0)
		{
			is_negative *= str[i - 1] == ' ';
			is_positive *= str[i - 1] == ' ';
		}
		if ((is_negative || is_positive) && ft_strlen(str) <= 1)
			return (FALSE);
		if (!(ft_isdigit(str[i]) || is_negative || is_positive))
			return (FALSE);
	}
	return (TRUE);
}

int	are_duplicates(int *numbers, int current_index)
{
	int	j;

	j = -1;
	while (++j < current_index)
	{
		if (numbers[j] == numbers[current_index])
			return (TRUE);
	}
	return (FALSE);
}
