/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:18:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 00:35:22 by svilla-d         ###   ########.fr       */
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
	int		min_index;

	current = head;
	min_index = 0;
	while (current != NULL)
	{
		min_node = find_min_node(head);
		if (min_node != NULL)
			min_node->index = min_index;
		current = current->next;
		min_index++;
	}
}
