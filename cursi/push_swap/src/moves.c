/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:05:37 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/12 09:16:41 by svilla-d         ###   ########.fr       */
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

void	move_both_positive(t_node **src, t_node **dst, t_node *node[], int nsrc)
{
	int	ndst;

	ndst = B;
	if (nsrc == B)
		ndst = A;
	while (node[nsrc]->cost > 0 && node[ndst]->cost > 0)
		rr(src, dst);
	move_node_to_top(src, node, nsrc);
	move_node_to_top(dst, node, ndst);
}

void	move_both_negative(t_node **src, t_node **dst, t_node *node[], int nsrc)
{
	int	ndst;

	ndst = B;
	if (nsrc == B)
		ndst = A;
	while (node[A]->cost < 0 && node[B]->cost < 0)
		rrr(src, dst);
	move_node_to_top(src, node, nsrc);
	move_node_to_top(dst, node, ndst);
}

void	move_pos_and_neg(t_node **src, t_node **dst, t_node *node[], int nsrc)
{
	int	ndst;

	ndst = B;
	if (nsrc == B)
		ndst = A;
	move_node_to_top(src, node, nsrc);
	move_node_to_top(dst, node, ndst);
}
