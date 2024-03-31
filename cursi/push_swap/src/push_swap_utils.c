/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:29:20 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 00:22:26 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_simple_error(void)
{
	ft_fprintf(STDERR_FILENO, "Error");
	exit(EXIT_FAILURE);
}

int	*parse_input(int argc, char **argv)
{
	int	i;
	int	*numbers;

	numbers = (int *)malloc((argc - 1) * sizeof(int));
	if (numbers == NULL)
		ft_simple_error();
	i = -1;
	while (++i < argc - 1)
		numbers[i] = ft_atoi(argv[i + 1]);
	return (numbers);
}

