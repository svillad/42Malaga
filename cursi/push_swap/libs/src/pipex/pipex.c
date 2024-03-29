/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:01:39 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/29 16:29:59 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_msg(int n, char	**files)
{
	int		i;
	char	*temp;

	i = 0;
	files[MSG] = ft_strdup("heredoc> ");
	while (i < n - 1)
	{
		temp = ft_strdup(files[MSG]);
		ft_free_str(files[MSG]);
		files[MSG] = ft_strjoin("pipe ", temp);
		ft_free_str(temp);
		i++;
	}
}

int	run_here_doc(int argc, char **argv, char **envp)
{
	int		n;
	char	*def_cmd;
	char	**commands;
	char	*files[5];

	def_cmd = "cat";
	if (argc < 4)
		return (ft_error("Invalid argument", "number arguments is incorrect\n"
				"Ex2: ./pipex here_doc LIM <cmds> <file>"));
	files[IN] = NULL;
	files[OUT] = argv[argc - 1];
	files[LIM] = argv[2];
	commands = &argv[3];
	n = argc - 4;
	if (argc == 4)
	{
		commands = &def_cmd;
		n = 1;
	}
	create_msg(n, files);
	return (pipex_process(n, commands, files, envp));
}

int	run_file_in(int argc, char **argv, char **envp)
{
	int		n;
	char	*def_cmd;
	char	**commands;
	char	*files[4];

	def_cmd = "cat";
	files[IN] = argv[1];
	files[OUT] = argv[argc - 1];
	files[LIM] = NULL;
	commands = &argv[2];
	n = argc - 3;
	if (argc == 3)
	{
		commands = &def_cmd;
		n = 1;
	}
	return (pipex_process(n, commands, files, envp));
}

int	pipex(int argc, char **argv, char **envp)
{
	if (argc < 3)
		return (ft_error("Invalid argument", "number arguments is incorrect\n"
				"Ex1: ./pipex <file1> <cmds> <file2>\n"
				"Ex2: ./pipex here_doc LIM <cmds> <file>"));
	if (ft_strnstr(argv[1], "here_doc", 8))
		return (run_here_doc(argc, argv, envp));
	return (run_file_in(argc, argv, envp));
}
