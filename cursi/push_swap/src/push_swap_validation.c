/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_validation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:07:59 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/12 12:19:51 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	validate_quantity(int argc, char **argv)
{
	char	*input;
	int		i;

	if (argc < 2)
		ft_simple_error();
	i = 0;
	while (++i < argc)
	{
		if (ft_strlen(argv[i]) == 0)
			ft_simple_error();
	}
	input = ft_join_args(argc, argv);
	if (ft_strlen(input) <= 1)
		ft_simple_error();
}

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
			is_negative = is_negative && str[i + 1] && ft_isdigit(str[i + 1]);
			is_positive = is_positive && str[i + 1] && ft_isdigit(str[i + 1]);
		}
		if (i > 0)
		{
			is_negative = is_negative && str[i - 1] && str[i - 1] == ' ';
			is_positive = is_positive && str[i - 1] && str[i - 1] == ' ';
		}
		if ((is_negative || is_positive) && ft_strlen(str) <= 1)
			return (FALSE);
		if (!(ft_isdigit(str[i]) || is_negative || is_positive))
			return (FALSE);
	}
	return (TRUE);
}

void	validate_types(int n, char **args)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (ft_strlen(args[i]) >= 10 && ft_strcmp(args[i], "2147483647") > 0)
			ft_simple_error();
		if (args[i][0] == '-' && ft_strlen(args[i]) >= 11 && ft_strcmp(args[i],
				"-2147483648") > 0)
			ft_simple_error();
		if (!are_digits(args[i]))
			ft_simple_error();
		i++;
	}
}

void	validate_duplicates(int n, char **args)
{
	int	i;
	int	j;
	int	*numbers;

	numbers = (int *)malloc(n * sizeof(int));
	if (numbers == NULL)
		ft_simple_error();
	i = -1;
	while (++i < n)
	{
		numbers[i] = ft_atoi(args[i]);
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
	int		n;
	char	**args;
	char	*input;

	validate_quantity(argc, argv);
	input = ft_join_args(argc, argv);
	args = ft_split(input, ' ');
	n = ft_count_words(input, ' ');
	free(input);
	validate_types(n, args);
	validate_duplicates(n, args);
	ft_free_double_ptr(args);
}
