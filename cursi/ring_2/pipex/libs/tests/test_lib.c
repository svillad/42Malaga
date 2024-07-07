/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lib.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:57:02 by svilla-d          #+#    #+#             */
/*   Updated: 2024/02/10 20:07:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>

#include "ft_printf.h"
#include "get_next_line.h"

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
	ft_printf("\n***************************");
	ft_printf(" -%d\n", ft_printf("Letras:%c,%c,%c", 'A', 'B', 'C'));
	ft_printf(" -%d\n", ft_printf("Palabras:%s,%s", "S3b@", "Villa"));
	ft_printf(" -%d\n", ft_printf("Num:%d,%d,%i,%d", 0, 123, -321, -123456789));
	ft_printf(" -%d\n", ft_printf("UNum:%u,%u,%u", 0, -321, -123456789));
	ft_printf(" -%d\n", ft_printf("Hex:%x,%X,%x,%X", 255, 128, 1022, -33));
	ft_printf(" -%d\n", ft_printf("Addr:%p,%p,%p,%p", &x, &c, &f, a));
	ft_printf(" -%d\n", ft_printf("Porcentaje:%%"));
	return (0);
}

int	test_ft_get_next_line(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;

	ft_printf("\n***************************");
	ft_printf("\n*   TEST: get_next_line   *");
	ft_printf("\n***************************");
	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	i = 0;
	while (i < 4)
	{
		ft_printf("\n");
		line = get_next_line(fd1);
		ft_printf("line 1[%d] (size:%d): %s", i + 1, ft_strlen(line), line);
		free(line);
		ft_printf("\n");
		line = get_next_line(fd2);
		ft_printf("line 2[%d] (size:%d): %s", i + 1, ft_strlen(line), line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}

int	main(void)
{
	test_ft_printf();
	test_ft_get_next_line();
	return (0);
}
