/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 17:18:46 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 14:23:38 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		node = (t_node){.value = numbers[i], .index = NOT_ASSIGNED,
			.position = i, .next = NULL};
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

void	print_stack(char *name, t_node *head)
{
	t_node	*current;

	if (head == NULL)
	{
		ft_printf("\t-\n");
		ft_printf("Stack\t%s\n", name);
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
	ft_printf("Stack\t%s\n", name);
}

void	print_stacks(t_node *a, t_node *b)
{
	t_node	*current_a;
	t_node	*current_b;

	current_a = a;
	current_b = b;
	while (current_a != NULL || current_b != NULL)
	{
		if (current_a != NULL)
		{
			ft_printf("[%d|%d]:\t%d", current_a->position, current_a->index,
				current_a->value);
			current_a = current_a->next;
		}
		else
			ft_printf("\t");
		if (current_b != NULL)
		{
			ft_printf("\t%d  :[%d|%d]", current_b->value, current_b->position,
				current_b->index);
			current_b = current_b->next;
		}
		ft_printf("\n");
	}
	ft_printf("\t-\t-\n");
	ft_printf("Stacks\ta\tb\n");
}

int	is_stack_ordered(t_node *a, t_node *b)
{
	t_node	*current;

	if (b != NULL)
		return (FALSE);
	current = a;
	while (current != NULL)
	{
		if (current->index != current->position)
			return (FALSE);
		current = current->next; 
	}
	return (TRUE);
}