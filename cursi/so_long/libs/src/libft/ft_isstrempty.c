/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isstrempty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:32:07 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/12 14:32:53 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_is_str_empty(const char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\r')
		{
			return (0);
		}
		str++;
	}
	return (1);
}
