/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:13 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/11 21:56:41 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		if (a->cost >= b->cost)
			return (a->cost);
		else
			return (b->cost);
	}
	if (a->cost <= 0 && b->cost <= 0)
	{
		if (a->cost <= b->cost)
			return (a->cost * -1);
		else
			return (b->cost * -1);
	}
	if (a->cost >= 0 && b->cost <= 0)
		return (a->cost + b->cost * -1);
	return (a->cost * -1 + b->cost);
}

t_node	*find_node_below(int index, t_node *head)
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
	if (node == NULL)
	{
		current = head;
		node = head;
		while (current != NULL && current->next != NULL)
		{
			if (current->next->index > current->index)
				node = current->next;
			current = current->next;
		}
	}
	return (node);
}

t_node	*find_node_above(int index, t_node *head)
{
	t_node	*current;
	t_node	*node;

	current = head;
	node = NULL;
	while (current != NULL)
	{
		if (current->index > index && (node == NULL
				|| current->index < node->index))
			node = current;
		current = current->next;
	}
	if (node == NULL)
	{
		current = head;
		node = head;
		while (current != NULL && current->next != NULL)
		{
			if (current->next->index < current->index)
				node = current->next;
			current = current->next;
		}
	}
	return (node);
}

t_node	**get_nodes_to_operate(t_node **src, t_node **dst, int nsrc, int ndst)
{
	t_node	*current[2];
	t_node	**operation_nodes;
	int		min_cost;
	int		cost;

	current[nsrc] = *src;
	operation_nodes = (t_node **)malloc(2 * sizeof(t_node *));
	min_cost = NOT_ASSIGNED;
	while (current[nsrc] != NULL)
	{
		if (nsrc == A)
			current[ndst] = find_node_below(current[nsrc]->index, *dst);
		else
			current[ndst] = find_node_above(current[nsrc]->index, *dst);
		cost = calculate_operation_cost(current[nsrc], current[ndst]);
		if (min_cost == NOT_ASSIGNED || cost < min_cost)
		{
			min_cost = cost;
			operation_nodes[nsrc] = current[nsrc];
			operation_nodes[ndst] = current[ndst];
		}
		current[nsrc] = current[nsrc]->next;
	}
	return (operation_nodes);
}

void	sort(t_node **a, t_node **b)
{
	t_node	**nodes;
	int		size;

	if (is_stack_ordered(*a, *b))
		return ;
	size = get_stack_len(*a);
	while (*a != NULL && size > 3 && !is_stack_partially_ordered(*a))
	{
		nodes = get_nodes_to_operate(a, b, A, B);
		operate(a, b, nodes, A);
		free(nodes);
		size--;
	}
	if (size == 2)
		ra(a);
	if (size == 3)
		sort_3_nodes(a);
	while (*b != NULL)
	{
		nodes = get_nodes_to_operate(b, a, B, A);
		operate(b, a, nodes, B);
		free(nodes);
	}
	sort_ascending(a);
}
