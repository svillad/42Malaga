/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 09:44:55 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/30 14:58:24 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str_dest;
	unsigned char	*str_src;

	str_dest = (unsigned char *)dest;
	str_src = (unsigned char *)src;
	if (!dest && !src)
		return (0);
	if (dest < src)
	{
		i = -1;
		while (++i < n)
			str_dest[i] = str_src[i];
	}
	else
	{
		while (n--)
			str_dest[n] = str_src[n];
	}
	return (dest);
}
