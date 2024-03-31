/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:52:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/01 01:27:10 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_op(t_node **dst, t_node **src)
{
	t_node	*temp;

	if (dst == NULL)
		return ;
	if (src == NULL || *src == NULL)
		return ;
	temp = *src;
	if (ft_strncmp((*src)->name, "a", 1) == 0)
		temp->name = "b";
	else
		temp->name = "a";
	(*src) = (*src)->next;
	if (*dst != NULL)
		temp->next = (*dst);
	else
		temp->next = NULL;
	(*dst) = temp;
	calculate_position(*dst);
	calculate_position(*src);
}

void	push(t_node **dst, t_node **src)
{
	if (src == NULL || *src == NULL)
    {
	    ft_printf("p%s\n", (*dst)->name);
		return ;
    }
	push_op(dst, src);
	ft_printf("p%s\n", (*dst)->name);
}
