/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:18:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/11 19:23:34 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_free_stack(t_node *head)
{
	t_node	*current;
	t_node	*next_node;

	current = head;
	while (current != NULL)
	{
		next_node = current->next;
		free(current);
		current = next_node;
	}
}

t_node	*find_min_node_without_index(t_node *head)
{
	t_node	*current;
	t_node	*min_node;

	current = head;
	while (current != NULL && current->index != NOT_ASSIGNED)
		current = current->next;
	min_node = current;
	while (current != NULL && current->next != NULL)
	{
		if (current->next->value < min_node->value
			&& current->next->index == NOT_ASSIGNED)
			min_node = current->next;
		current = current->next;
	}
	return (min_node);
}

void	set_stack_indexes(t_node *head)
{
	t_node	*current;
	t_node	*min_node;
	int		index;

	current = head;
	index = 0;
	while (current != NULL)
	{
		min_node = find_min_node_without_index(head);
		if (min_node != NULL)
			min_node->index = index;
		current = current->next;
		index++;
	}
}

void	sort_descending(t_node **head)
{
	t_node	*current;
	t_node	*max_node;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	max_node = *head;
	while (current != NULL)
	{
		if (current->index > max_node->index)
			max_node = current;
		current = current->next;
	}
	while (max_node->cost > 0)
	{
		rb(head);
	}
	while (max_node->cost < 0)
	{
		rrb(head);
	}
}

void	sort_ascending(t_node **head)
{
	t_node	*current;
	t_node	*min_node;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	min_node = *head;
	while (current != NULL)
	{
		if (current->index < min_node->index)
			min_node = current;
		current = current->next;
	}
	while (min_node->cost > 0)
	{
		ra(head);
	}
	while (min_node->cost < 0)
	{
		rra(head);
	}
}
