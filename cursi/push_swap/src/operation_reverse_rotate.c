/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_reverse_rotate.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 00:48:27 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate_op(t_node **head)
{
	t_node	*penultimate_node;
	t_node	*last_node;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return ;
	penultimate_node = get_penultimate_node(*head);
	last_node = get_last_node(*head);
	penultimate_node->next = NULL;
	last_node->next = *head;
	(*head) = last_node;
	calculate_position(*head);
}

void	reverse_rotate(t_node **head)
{
	if (head == NULL || *head == NULL)
	{
		ft_printf("rr-\n");
		return ;
	}
	reverse_rotate_op(head);
	ft_printf("rr%s\n", (*head)->name);
}

void	double_reverse_rotate(t_node **a, t_node **b)
{
	if (a == NULL || *a == NULL || (*a)->next == NULL)
	{
		ft_printf("rrr\n");
		return ;
	}
	reverse_rotate_op(a);
	if (b == NULL || *b == NULL || (*b)->next == NULL)
	{
		ft_printf("rrr\n");
		return ;
	}
	reverse_rotate_op(b);
	ft_printf("rrr\n");
}
