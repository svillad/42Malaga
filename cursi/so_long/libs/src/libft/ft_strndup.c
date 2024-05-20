/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:07:43 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 13:16:42 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	size;
	size_t	len;
	char	*dest;

	len = 0;
	while (src[len] != '\0')
		len++;
	size = n;
	if (n < (len + 1))
		size = len + 1;
	dest = (char *)malloc(size);
	if (!dest)
		return (0);
	i = -1;
	while (src && ++i < len)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	dest[i] = '\0';
	return (dest);
}
