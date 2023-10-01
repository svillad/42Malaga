/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 13:37:52 by svilla-d          #+#    #+#             */
/*   Updated: 2023/10/01 17:19:15 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_list	*ft_create_node(void *content, void *(*f)(void *))
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = f(content);
	new_node->next = NULL;
	return (new_node);
}

static void	ft_add_node(t_list **result, t_list **last, t_list *new_node)
{
	if (!*result)
	{
		*result = new_node;
		*last = new_node;
	}
	else
	{
		(*last)->next = new_node;
		*last = new_node;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*last;
	t_list	*new_node;

	if (!lst || !f)
		return (NULL);
	result = NULL;
	while (lst)
	{
		new_node = ft_create_node(lst->content, f);
		if (!new_node)
		{
			if (del)
				ft_lstclear(&result, del);
			return (NULL);
		}
		ft_add_node(&result, &last, new_node);
		lst = lst->next;
	}
	return (result);
}
