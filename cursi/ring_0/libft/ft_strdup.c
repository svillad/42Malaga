/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:07:43 by svilla-d          #+#    #+#             */
/*   Updated: 2023/09/30 10:12:55 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	size_t	i;
	size_t	len;
	char	*dest;

	len = 0;
	while (src[len] != '\0')
		len++;
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (0);
	i = -1;
	while (++i < len)
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	dest[len] = '\0';
	return (dest);
}
