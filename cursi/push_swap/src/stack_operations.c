/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:18:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/31 19:21:51 by svilla-d         ###   ########.fr       */
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

t_node	*create_node(t_node *head, int value, int position, t_node *prev_node)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
	{
		ft_free_stack(head);
		ft_simple_error();
	}
	new_node->value = value;
	new_node->index = NOT_ASSIGNED;
	new_node->position = position;
	new_node->next = NULL;
	new_node->prev = prev_node;
	if (prev_node != NULL)
		prev_node->next = new_node;
	return (new_node);
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

void	set_index(t_node *head)
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

t_node	*init_stack(int *numbers, int size)
{
	t_node	*head;
	t_node	*prev_node;
	int		i;
	t_node	*new_node;

	head = NULL;
	prev_node = NULL;
	i = 0;
	while (i < size)
	{
		new_node = create_node(head, numbers[i], i, prev_node);
		if (head == NULL)
			head = new_node;
		prev_node = new_node;
		i++;
	}
	set_index(head);
	return (head);
}
