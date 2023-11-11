/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:57:02 by svilla-d          #+#    #+#             */
/*   Updated: 2023/11/11 13:08:25 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "stdio.h"
#include <limits.h>

int	main(void)
{
	int			x;
	char		c;
	float		f;
	const char	a[1] = {2};

	x = 2;
	c = 2;
	f = 2;
	printf("%d: ", printf("Letras:%c,%c,%c\n", 'A', 'B', 'C'));
	printf("%d: ", ft_printf("Letras:%c,%c,%c\n", 'A', 'B', 'C'));
	printf("%d: ", printf("Palabras:%s,%s,%s\n", "S3b@s", "Villa", "Duarte"));
	printf("%d: ", ft_printf("Palabras:%s,%s,%s\n", "S3b@", "Villa", "Duarte"));
	printf("%d: ", printf("Num:%d,%d,%i,%d\n", 0, 123, -321, -123456789));
	printf("%d: ", ft_printf("Num:%d,%d,%i,%d\n", 0, 123, -321, -123456789));
	printf("%d: ", printf("UNum:%u,%u,%u,%u\n", 0, 123, -321, -123456789));
	printf("%d: ", ft_printf("UNum:%u,%u,%u,%u\n", 0, 123, -321, -123456789));
	printf("%d: ", printf("Hex:%x,%X,%x,%X\n", 255, 128, 1022, -33));
	printf("%d: ", ft_printf("Hex:%x,%X,%x,%X\n", 255, 128, 1022, -33));
	printf("%d: ", printf("Addr:%p,%p,%p,%p\n", &x, &c, &f, a));
	printf("%d: ", ft_printf("Addr:%p,%p,%p,%p\n", &x, &c, &f, a));
	printf("%d: ", printf("Porcentaje:%%\n"));
	printf("%d: ", ft_printf("Porcentaje:%%\n"));
	return (0);
}
