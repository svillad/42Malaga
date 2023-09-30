/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:26:17 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/30 13:21:41 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *ptr, int value, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	c;

	i = 0;
	str = (unsigned char *)ptr;
	c = (unsigned char)value;
	while (i < n)
	{
		if (str[i] == c)
			return (&str[i]);
		i++;
	}
	return (0);
}
