/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 13:35:44 by svilla-d         ###   ########.fr       */
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

void	ra(t_node **head)
{
	if (head == NULL || *head == NULL)
	{
		ft_printf("ra\n");
		return ;
	}
	rotate_op(head);
	ft_printf("ra\n");
}

void	rb(t_node **head)
{
	if (head == NULL || *head == NULL)
	{
		ft_printf("rb\n");
		return ;
	}
	rotate_op(head);
	ft_printf("rb\n");
}

void	rr(t_node **a, t_node **b)
{
	if (a == NULL || *a == NULL)
	{
		ft_printf("rr\n");
		return ;
	}
	rotate_op(a);
	if (b == NULL || *b == NULL)
	{
		ft_printf("rr\n");
		return ;
	}
	rotate_op(b);
	ft_printf("rr\n");
}
