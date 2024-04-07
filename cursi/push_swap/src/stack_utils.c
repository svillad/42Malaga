/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:18:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/07 23:01:48 by svilla-d         ###   ########.fr       */
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

t_node	*find_min_node(t_node *head)
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
		min_node = find_min_node(head);
		if (min_node != NULL)
			min_node->index = index;
		current = current->next;
		index++;
	}
}

void	flush_stack(t_node **dst, t_node **src)
{
	t_node	*current;

	current = *src;
	while (*src != NULL)
	{
		pa(dst, src);
		if (current->next != NULL)
			current = current->next;
	}
}

void	sort_stack(t_node **head)
{
	t_node	*current;
	t_node	*max_node;

	current = *head;
	max_node = *head;
	while (current != NULL)
	{
		if (current->index > max_node->index)
			max_node = current;
		current = current->next;
	}
	while (max_node->cost > 0)
		rb(head);
	while (max_node->cost < 0)
		rrb(head);
}
