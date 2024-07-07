/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_printf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:57:02 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/29 18:54:01 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include "ft_printf.h"

int	test_ft_printf(void)
{
	int			x;
	char		c;
	float		f;
	const char	a[1] = {2};

	x = 2;
	c = 2;
	f = 2;
	ft_printf("\n***************************");
	ft_printf("\n*     TEST: ft_printf     *");
	ft_printf("\n***************************\n");
	ft_printf(" :%d\n", ft_printf("Letras:%c,%c,%c", 'A', 'B', 'C'));
	ft_printf("123456789.12 :12\n\n");
	ft_printf(" :%d\n", ft_printf("Palabras:%s,%s", "S3b@", "Villa"));
	ft_printf("123456789.123456789 :19\n\n");
	ft_printf(" :%d\n", ft_printf("Num:%d,%d,%i,%d", 0, 123, -321, -123456789));
	ft_printf("123456789.123456789.12345 :25\n\n");
	ft_printf(" :%d\n", ft_printf("UNum:%u,%u,%u", 0, -321, -123456789));
	ft_printf("123456789.123456789.12345678 :28\n\n");
	ft_printf(" :%d\n", ft_printf("Hex:%x,%X,%x,%X", 255, 128, 1022, -33));
	ft_printf("123456789.123456789.12 :22\n\n");
	ft_printf(" :%d\n", ft_printf("Addr:%p,%p,%p,%p", &x, &c, &f, a));
	ft_printf("123456789.123456789.123456789.123456789.123456789.12 :52\n\n");
	ft_printf(" :%d\n", ft_printf("Porcentaje:%%"));
	return (0);
}

int	main(void)
{
	test_ft_printf();
	return (0);
}
