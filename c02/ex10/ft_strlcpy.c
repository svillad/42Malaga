/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 02:07:07 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/10 02:07:50 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

unsigned int	ft_strlen(char *str);
unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);

unsigned int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++ != '\0')
		len++;
	return (len);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	src_len;

	if (dest == src)
	{
		*dest = '\0';
		return (0);
	}
	src_len = ft_strlen(src);
	i = 0;
	while (*(src + i) != '\0' && i < size - 1)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = '\0';
	return (src_len);
}

int	main(void)
{
	char origen[] = "0123456789";
	char destino[10] = "";
	unsigned int	r;

	printf("%s :: %s\n", destino, origen);

	// r = strlcpy(destino, origen, 10);
	r = ft_strlcpy(destino, origen, 10);

	printf("%s :: %s -> %u\n", destino, origen, r);
	return (0);
}