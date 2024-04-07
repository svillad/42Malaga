/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:05:37 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/07 23:03:17 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_node_to_top(t_node **head, t_node *node[], int stack)
{
	if (stack == A)
	{
		while (node[stack]->cost > 0)
			ra(head);
		while (node[stack]->cost < 0)
			rra(head);
	}
	else
	{
		while (node[stack]->cost > 0)
			rb(head);
		while (node[stack]->cost < 0)
			rrb(head);
	}
}

void	move_both_positive(t_node **a, t_node **b, t_node *node[])
{
	while (node[A]->cost > 0 && node[B]->cost > 0)
		rr(a, b);
	move_node_to_top(a, node, A);
	move_node_to_top(b, node, B);
}

void	move_both_negative(t_node **a, t_node **b, t_node *node[])
{
	while (node[A]->cost < 0 && node[B]->cost < 0)
		rrr(a, b);
	move_node_to_top(a, node, A);
	move_node_to_top(b, node, B);
}

void	move_pos_and_neg(t_node **a, t_node **b, t_node *node[])
{
	move_node_to_top(a, node, A);
	move_node_to_top(b, node, B);
}
