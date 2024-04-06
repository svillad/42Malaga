/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:13 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/06 19:37:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*search_prev_node(int index, t_node *head)
{
	t_node	*current;
	t_node	*node;

	current = head;
	node = head;
	while (current->next != NULL)
	{
		if (current->index < index && current->index > node->index)
			node = current;
		current = current->next;
	}
	return node;
}

void	calculate_next(t_node *a, t_node *b)
{
	t_node	*current;
	int		total_cost;
	int		min_cost;
	t_node	*node;

	total_cost = 0;
	min_cost = 0;
	current = a;
	while (current != NULL)
	{
		print_node(current);
		node = search_prev_node(current->index, b);
		ft_printf(" prev:");
		print_node(node);
		current = current->next;
		ft_printf("\n");

	}
}

void	next_move(t_node **a, t_node **b)
{
	int	x;

	x = 1;
	while (x != 0)
	{
		scanf("%d", &x);
		calculate_next(*a, *b);
	}
}

void	sort(t_node **a, t_node **b)
{
	print_stacks(*a, *b);
	if (get_stack_len(*a) <= 3)
		ft_printf("<3\n");
	else
	{
		pb(b, a);
		if (get_stack_len(*a) > 3)
			pb(b, a);
	}
	print_stacks(*a, *b);
	next_move(a, b);
}
