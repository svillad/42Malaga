/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_push_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:03:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/04/20 20:39:42 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "push_swap.h"
#include "pipex.h"

void	test_case(char *case_name, char *str)
{
	int		argc;
	char	**argv;

	argc = ft_count_words(str, ' ');
	argv = ft_split(str, ' ');
	ft_printf("\n----- %s -----\n", case_name);
	ft_printf("%s\n", str);
	push_swap(argc, argv);
	free(argv);
}

int	test_push_swap(int argc, char **argv)
{
	(void)(argc);
	(void)(argv);
	ft_printf("\n***************************");
	ft_printf("\n*     TEST: push_swap     *");
	ft_printf("\n***************************\n");
	test_case("Test_0", "./push_swap 1 2 3 4 5");
	test_case("Test_1", "./push_swap 3 2 1");
	test_case("Test_2", "./push_swap 5 4 3 2 1");
	return (0);
}

int	main(int argc, char **argv)
{
	test_push_swap(argc, argv);
	return (0);
}
