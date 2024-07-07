/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:03:58 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/29 18:47:37 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "get_next_line.h"
#include "pipex.h"

void	print_file_contents(const char *filename)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_error(NULL, "error open file");
		return ;
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_printf("line 1[%d] (size:%d):\t%s", i + 1, ft_strlen(line), line);
		free(line);
		i++;
	}
	close(fd);
}

void	test_case(char *case_name, char *str, char **env)
{
	int		argc;
	char	**argv;

	argc = ft_count_words(str, ' ');
	argv = ft_split(str, ' ');
	ft_printf("\n----- %s -----\n", case_name);
	pipex(argc, argv, env);
	print_file_contents(argv[argc - 1]);
	free(argv);
}

int	test_pipex(int argc, char **argv, char **env)
{
	(void)(argc);
	(void)(argv);
	ft_printf("\n***************************");
	ft_printf("\n*       TEST: pipex       *");
	ft_printf("\n***************************\n");
	test_case("CAT", "./pipex tests/test3.txt output.txt", env);
	test_case("SORT", "./pipex tests/test3.txt sort output.txt", env);
	test_case("UNIQ", "./pipex tests/test3.txt sort uniq output.txt", env);
	test_case("WC", "./pipex tests/test3.txt sort uniq wc output.txt", env);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	test_pipex(argc, argv, env);
	return (0);
}
