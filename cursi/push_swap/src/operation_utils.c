/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/06 17:30:08 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	calculate_costs(t_node *head)
{
	t_node	*current;
	int		size;
	int		median;
	int		cost;

	current = head;
	size = get_stack_len(head);
	median = size / 2;
	while (current != NULL)
	{
		if (current->position <= median)
			cost = current->position;
		else
			cost = current->position - size;
		current->cost = cost;
		current = current->next;
	}
}

void	calculate_positions(t_node *head)
{
	t_node	*current;
	int		i;

	i = 0;
	current = head;
	while (current != NULL)
	{
		current->position = i;
		current = current->next;
		i++;
	}
	calculate_costs(head);
}

t_node	*get_penultimate_node(t_node *head)
{
	t_node	*current;

	if (head == NULL)
		return (NULL);
	current = head;
	while (current->next != NULL && current->next->next != NULL)
	{
		current = current->next;
	}
	return (current);
}

t_node	*get_last_node(t_node *head)
{
	t_node	*current;

	if (head == NULL)
		return (NULL);
	current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	return (current);
}
