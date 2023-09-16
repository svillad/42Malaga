/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 09:45:44 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 01:59:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strcpy(char *dest, char *src);

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	if (dest == src)
	{
		*dest = '\0';
		return (NULL);
	}
	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (dest);
}

int	main(void)
{
	char origen[10] = "123456789";
	char destino[10] = "";
	char *r = NULL;

	printf("%s :: %s\n", destino, origen);
	printf("%p, %p :: %p\n", destino, origen, r);

	// r = strcpy(destino, origen);
	r = ft_strcpy(destino, origen);

	printf("%s :: %s\n", destino, origen);
	printf("%p, %p :: %p\n", destino, origen, r);
	return (0);
}