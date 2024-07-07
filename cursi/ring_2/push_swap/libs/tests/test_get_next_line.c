/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_next_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:25:31 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/29 18:43:31 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <limits.h>
#include "ft_printf.h"
#include "get_next_line.h"

int	test_ft_get_next_line(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;

	ft_printf("\n***************************");
	ft_printf("\n*   TEST: get_next_line   *");
	ft_printf("\n***************************\n");
	fd1 = open("tests/test1.txt", O_RDONLY);
	fd2 = open("tests/test2.txt", O_RDONLY);
	i = 0;
	while (i < 4)
	{
		ft_printf("\n");
		line = get_next_line(fd1);
		ft_printf("line[%d] (size:%d) 1: %s", i + 1, ft_strlen(line), line);
		free(line);
		ft_printf("\n");
		line = get_next_line(fd2);
		ft_printf("line[%d] (size:%d) 2: %s", i + 1, ft_strlen(line), line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}

int	main(void)
{
	test_ft_get_next_line();
	return (0);
}
