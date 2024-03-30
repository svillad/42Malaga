/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:07:59 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/30 20:43:45 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	validate_quantity(int argc)
{
	if (argc < 2)
		ft_simple_error();
}

int	are_digits(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(ft_isdigit(str[i])
				|| (str[i] == '-' && str[i + 1] && ft_isdigit(str[i + 1]))
				|| (str[i] == '+' && str[i + 1] && ft_isdigit(str[i + 1]))))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	validate_types(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!are_digits(argv[i]))
			ft_simple_error();
		i++;
	}
}

void	validate_duplicates(int argc, char **argv)
{
	int	i;
	int	j;
	int	*numbers;

	numbers = (int *)malloc(argc * sizeof(int));
	if (numbers == NULL)
		ft_simple_error();
	i = -1;
	while (++i < argc - 1)
	{
		numbers[i] = ft_atoi(argv[i + 1]);
		j = -1;
		while (++j < i)
		{
			if (numbers[j] == numbers[i])
			{
				free(numbers);
				ft_simple_error();
			}
		}
	}
	free(numbers);
}

void	validate_input(int argc, char **argv)
{
	validate_quantity(argc);
	validate_types(argc, argv);
	validate_duplicates(argc, argv);
}
