/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 08:19:33 by svilla-d          #+#    #+#             */
/*   Updated: 2023/10/01 11:54:27 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *ptr, int value, size_t n)
{
	unsigned char	*str;
	unsigned char	c;

	str = (unsigned char *)ptr;
	c = (unsigned char)value;
	while (n > 0)
	{
		*str = c;
		str++;
		n--;
	}
	return (ptr);
}
