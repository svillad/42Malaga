/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 00:48:00 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_op(t_node **head)
{
	t_node	*last_node;
	t_node	*temp;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return ;
	last_node = get_last_node(*head);
	temp = *head;
	(*head) = (*head)->next;
	temp->next = NULL;
	last_node->next = temp;
	calculate_position(*head);
}

void	rotate(t_node **head)
{
	if (head == NULL || *head == NULL)
	{
		ft_printf("r-\n");
		return ;
	}
	rotate_op(head);
	ft_printf("r%s\n", (*head)->name);
}

void	double_rotate(t_node **a, t_node **b)
{
	if (a == NULL || *a == NULL || (*a)->next == NULL)
	{
		ft_printf("rr\n");
		return ;
	}
	rotate_op(a);
	if (b == NULL || *b == NULL || (*b)->next == NULL)
	{
		ft_printf("rr\n");
		return ;
	}
	rotate_op(b);
	ft_printf("rr\n");
}
