/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:40:04 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 01:15:14 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	int		*numbers;
	t_node	*a;
	t_node	*b;

	validate_input(argc, argv);
	numbers = parse_input(argc, argv);
	a = init_stack(numbers, argc - 1);
	print_stack(a);
	swap(&a);
	print_stack(a);
	double_rotate(&a, &a);
	print_stack(a);
	reverse_rotate(&a);
	print_stack(a);
	b = NULL;
	push(&b, &a);
	push(&b, &a);
	print_stack(a);
	print_stack(b);
	
	push(&a, &b);
	push(&a, &b);
	print_stack(a);
	print_stack(b);

	free(numbers);
	ft_free_stack(a);
	return (0);
}
