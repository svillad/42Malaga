/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:13 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/11 22:12:45 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	operate(t_node **src, t_node **dst, t_node *node[], int nsrc)
{
	int	ndst;

	ndst = B;
	if (nsrc == B)
		ndst = A;
	if (node[ndst] == NULL)
		move_node_to_top(src, node, nsrc);
	else if (node[nsrc]->cost >= 0 && node[ndst]->cost >= 0)
		move_both_positive(src, dst, node, nsrc);
	else if (node[nsrc]->cost <= 0 && node[ndst]->cost <= 0)
		move_both_negative(src, dst, node, nsrc);
	else if (node[nsrc]->cost >= 0 && node[ndst]->cost <= 0)
		move_pos_and_neg(src, dst, node, nsrc);
	else if (node[nsrc]->cost <= 0 && node[ndst]->cost >= 0)
		move_pos_and_neg(src, dst, node, nsrc);
	if (nsrc == A && !is_stack_ordered(*src, *dst))
		pb(dst, src);
	else if (nsrc == B)
		pa(dst, src);
}

void	sort_3_nodes(t_node **head)
{
	const int	n0 = (*head)->index;
	const int	n1 = (*head)->next->index;
	const int	n2 = (*head)->next->next->index;

	if (n1 > n2 && n2 > n0)
	{
		rra(head);
		sa(head);
	}
	else if (n2 > n0 && n0 > n1)
		sa(head);
	else if (n1 > n0 && n0 > n2)
		rra(head);
	else if (n0 > n2 && n2 > n1)
		ra(head);
	else if (n0 > n1 && n1 > n2)
	{
		ra(head);
		sa(head);
	}
}

void	get_min_max_index(t_node *head, int *min_index, int *max_index)
{
	t_node	*current;

	if (head == NULL)
	{
		*min_index = -1;
		*max_index = -1;
		return ;
	}
	current = head;
	*min_index = head->index;
	*max_index = head->index;
	while (current != NULL)
	{
		if (current->index < *min_index)
		{
			*min_index = current->index;
		}
		if (current->index > *max_index)
		{
			*max_index = current->index;
		}
		current = current->next;
	}
}

int	is_stack_partially_ordered(t_node *head)
{
	t_node	*current;
	t_node	*last_node;
	int		max_index;
	int		min_index;

	current = head;
	get_min_max_index(head, &min_index, &max_index);
	last_node = get_last_node(head);
	while (current != NULL && current->next != NULL)
	{
		if (current->index > current->next->index
			&& (current->index != max_index
				|| current->next->index != min_index))
			return (FALSE);
		if (head->index < last_node->index && (head->index != min_index
				|| last_node->index != max_index))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}
