/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:01:39 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/06 10:24:06 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

#ifdef BONUS

int	main(int argc, char **argv, char **envp)
{
	int		n;
	char	*def_cmd;
	char	**commands;
	char	*files[2];

	def_cmd = "cat";
	if (argc < 3)
		return (ft_error("Invalid argument", "number of arguments is incorrect\n"
				"Ex: ./pipex <file1> <cmd1> <file2>"));
	files[0] = argv[1];
	commands = &argv[2];
	files [1] = argv[argc - 1];
	n = argc - 3;
	if (argc == 3)
	{
		commands = &def_cmd;
		n = 1;
	}
	return (pipex(n, commands, files, envp));
}
#else

int	main(int argc, char **argv, char **envp)
{
	int		n;
	char	**commands;
	char	*files[2];

	if (argc != 5)
		return (ft_error("Invalid argument", "number of arguments is incorrect\n"
				"Ex: ./pipex <file1> <cmd1> <cmd2> <file2>"));
	files[0] = argv[1];
	commands = &argv[2];
	files [1] = argv[argc - 1];
	n = argc - 3;
	return (pipex(n, commands, files, envp));
}
#endif
