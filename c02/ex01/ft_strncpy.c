/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:56:35 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/09 10:13:24 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n);

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;
	if (dest == src)
	{
		*dest = '\0';
		return (NULL);
	}
	i = 0;
	while (*(src + i) != '\0' && i != n)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	while (i < n)
	{
		*(dest + i) = '\0';
		i++;
	}
	n++;
	return (dest);
}

int	main(void)
{
	char origen[10] = "ABCDEFGHI";
	char destino[5] = "";
	char *r = NULL;

	printf("%s :: %s\n", destino, origen);
	printf("%p, %p :: %p\n", destino, origen, r);

	// r = strncpy(destino, origen, 5);
	r = ft_strncpy(destino, origen, 5);

	printf("%s :: %s\n", destino, origen);
	printf("%p, %p :: %p\n", destino, origen, r);
	printf("%lu, %lu\n", sizeof(destino), sizeof(origen));
	return (0);
}