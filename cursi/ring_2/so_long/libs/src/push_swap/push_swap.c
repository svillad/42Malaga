/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:40:04 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/20 20:02:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	push_swap(int argc, char **argv)
{
	int		*numbers;
	t_node	*a;
	t_node	*b;
	int		size;

	validate_input(argc, argv);
	numbers = parse_input(argc, argv, &size);
	a = init_stack(numbers, size);
	b = NULL;
	sort(&a, &b);
	free(numbers);
	ft_free_stack(a);
	return (0);
}