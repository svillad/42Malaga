/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/02 20:38:14 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(char **argv, char **envp, int *fd)
{
	int		input_file;
	char	**cmd;
	char	*path;

	input_file = open(argv[1], O_RDONLY);
	if (input_file == -1)
		ft_error(NULL, argv[1]);
	cmd = ft_split(argv[2], ' ');
	path = ft_find_cmd_path(cmd[0], envp);
	if (!path)
	{
		ft_error("command not found", cmd[0]);
		ft_free(cmd);
		close(fd[0]);
	}
	else
	{
		dup2(input_file, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		if (execve(path, cmd, envp) == -1)
			ft_error("could not execute command", cmd[0]);
	}
}

void	parent_process(char **argv, char **envp, int *fd)
{
	int		output_file;
	char	**cmd;
	char	*path;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file == -1)
		ft_error(NULL, argv[4]);
	cmd = ft_split(argv[3], (int)32);
	path = ft_find_cmd_path(cmd[0], envp);
	if (!path)
	{
		ft_error("command not found", cmd[0]);
		ft_free(cmd);
		close(fd[1]);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(output_file, STDOUT_FILENO);
		close(fd[1]);
		if (execve(path, cmd, envp) == BAD)
			ft_error("could not execute command", cmd[0]);
	}
}
