/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 10:02:59 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/30 14:45:23 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	len;
	size_t	i;

	len = 0;
	while (src[len] != '\0')
		len++;
	if (n == 0)
		return (len);
	i = 0;
	while (i < n - 1 && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}
