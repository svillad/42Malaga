/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 14:10:02 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_op(t_node **head)
{
	t_node	*temp;

	if (head == NULL || *head == NULL || (*head)->next == NULL)
		return ;
	temp = (*head)->next;
	(*head)->next = (*head)->next->next;
	temp->next = (*head);
	(*head) = temp;
	swap_positions(head, &(*head)->next);
}

void	sa(t_node **head)
{
	if (head == NULL || *head == NULL)
	{
		ft_printf("sa\n");
		return ;
	}
	swap_op(head);
	ft_printf("sa\n");
}

void	sb(t_node **head)
{
	if (head == NULL || *head == NULL)
	{
		ft_printf("sb\n");
		return ;
	}
	swap_op(head);
	ft_printf("sb\n");
}

void	ss(t_node **a, t_node **b)
{
	if (a == NULL || *a == NULL)
	{
		ft_printf("ss\n");
		return ;
	}
	swap_op(a);
	if (b == NULL || *b == NULL)
	{
		ft_printf("ss\n");
		return ;
	}
	swap_op(b);
	ft_printf("ss\n");
}
