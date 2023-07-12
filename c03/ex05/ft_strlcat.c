/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:34:58 by svilla-d          #+#    #+#             */
/*   Updated: 2023/07/12 12:41:10 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size);
int				ft_strlen(char *str);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++ != '\0')
		len++;
	return (len);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	total_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	total_len = dest_len + src_len;
	if (size < dest_len)
		return (size + src_len);
	i = dest_len;
	j = 0;
	while (*(src + j) && i < size - 1 && size > 0)
	{
		*(dest + i) = *(src + j);
		i++;
		j++;
	}
	*(dest + i) = '\0';
	return (total_len);
}

// int	main(void)
// {
// 	char palabra1[6] = "ABCDE";
// 	char destino_a[20] = "123";
// 	char destino_b[20] = "123";
// 	int ra, rb;
// 	unsigned int n = 10;

// 	ra = strlcat(destino_a, palabra1, n);
// 	printf("%s, %s :: %d\n", palabra1, destino_a, ra);

// 	rb = ft_strlcat(destino_b, palabra1, n);
// 	printf("%s, %s :: %d\n", palabra1, destino_b, rb);

// 	return (0);
// }