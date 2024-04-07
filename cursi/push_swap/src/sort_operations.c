/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:13 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/07 23:04:14 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	operate(t_node **a, t_node **b, t_node *node[])
{
	if (node[B] == NULL)
		move_node_to_top(a, node, A);
	else if (node[A]->cost >= 0 && node[B]->cost >= 0)
		move_both_positive(a, b, node);
	else if (node[A]->cost <= 0 && node[B]->cost <= 0)
		move_both_negative(a, b, node);
	else if (node[A]->cost >= 0 && node[B]->cost <= 0)
		move_pos_and_neg(a, b, node);
	else if (node[A]->cost <= 0 && node[B]->cost >= 0)
		move_pos_and_neg(a, b, node);
	pb(b, a);
}

int	calculate_operation_cost(t_node *a, t_node *b)
{
	if (b == NULL)
	{
		if (a->cost >= 0)
			return (a->cost);
		else
			return (a->cost * -1);
	}
	if (a->cost >= 0 && b->cost >= 0)
	{
		if (a->cost > b->cost)
			return (a->cost);
		else
			return (b->cost);
	}
	if (a->cost <= 0 && b->cost <= 0)
	{
		if (a->cost < b->cost)
			return (a->cost * -1);
		else
			return (b->cost * -1);
	}
	if (a->cost >= 0 && b->cost <= 0)
		return (a->cost + b->cost * -1);
	return (a->cost * -1 + b->cost);
}

t_node	*find_adjacent_node(int index, t_node *head)
{
	t_node	*current;
	t_node	*node;

	current = head;
	node = NULL;
	while (current != NULL)
	{
		if (current->index < index && (node == NULL
				|| current->index > node->index))
			node = current;
		current = current->next;
	}
	return (node);
}

void	sort(t_node **a, t_node **b)
{
	t_node	*current_node[2];
	t_node	*operation_node[2];
	int		min_cost;
	int		cost;

	while (*a != NULL)
	{
		min_cost = -1;
		current_node[A] = *a;
		while (current_node[A] != NULL)
		{
			current_node[B] = find_adjacent_node(current_node[A]->index, *b);
			cost = calculate_operation_cost(current_node[A], current_node[B]);
			if (min_cost == -1 || cost < min_cost)
			{
				min_cost = cost;
				operation_node[A] = current_node[A];
				operation_node[B] = current_node[B];
			}
			current_node[A] = current_node[A]->next;
		}
		operate(a, b, operation_node);
	}
	sort_stack(b);
	flush_stack(a, b);
}
