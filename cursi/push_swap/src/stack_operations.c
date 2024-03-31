/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:18:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 01:28:11 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_stack_len(t_node *head)
{
	int		len;
	t_node	*current;

	if (head == NULL)
		return (0);
	len = 0;
	current = head;
	while (current->next != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}

t_node	*init_stack(int *numbers, int size)
{
	t_node	*head;
	t_node	*prev_node;
	int		i;
	t_node	*new_node;
	t_node	node;

	head = NULL;
	prev_node = NULL;
	i = -1;
	while (++i < size)
	{
		node = (t_node){
			.name = "a",
			.value = numbers[i], .index = NOT_ASSIGNED,
			.position = i, .next = NULL
		};
		new_node = create_node(head, node);
		if (prev_node != NULL)
			prev_node->next = new_node;
		if (head == NULL)
			head = new_node;
		prev_node = new_node;
	}
	set_stack_indexes(head);
	return (head);
}

void	print_stack(t_node *head)
{
	t_node	*current;

	if (head == NULL)
	{
		ft_printf("\t-\n");
		ft_printf("Stack\t-\n");
		return ;
	}
	current = head;
	while (current != NULL)
	{
		ft_printf("[%d|%d]:\t%d\n", current->position, current->index,
			current->value);
		current = current->next;
	}
	ft_printf("\t-\n");
	ft_printf("Stack\t%s\n", head->name);
}
