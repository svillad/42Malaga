/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 00:31:42 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_positions(t_node **node1, t_node **node2)
{
	int	position;

	if (node1 == NULL || *node1 == NULL)
		return ;
	if (node2 == NULL || *node2 == NULL)
		return ;
	position = (*node1)->position;
	(*node1)->position = (*node2)->position;
	(*node2)->position = position;
}

void	calculate_position(t_node *head)
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
