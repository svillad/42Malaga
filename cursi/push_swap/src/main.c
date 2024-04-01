/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:40:04 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 14:24:03 by svilla-d         ###   ########.fr       */
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
	b = NULL;
	ft_printf("Ordered: %d\n",is_stack_ordered(a, b));
	print_stacks(a, b);
	sa(&a);
	print_stacks(a, b);
	rr(&a, &b);
	print_stacks(a, b);
	rra(&a);
	print_stacks(a, b);
	ft_printf("Ordered: %d\n",is_stack_ordered(a, b));
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	pb(&b, &a);
	print_stacks(a, b);
	free(numbers);
	ft_free_stack(a);
	ft_printf("Ordered: %d\n",is_stack_ordered(a, b));

	return (0);
}
