/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/06 10:03:30 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	execute_command(char **cmd, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(cmd[0], ' ');
	if (!command)
	{
		ft_error("command is empty", cmd[0]);
		return (ERROR);
	}
	path = ft_find_cmd_path(command[0], envp);
	if (!path)
	{
		ft_error("command not found", cmd[0]);
		ft_free(command);
		return (ERROR);
	}
	if (execve(path, command, envp) == ERROR)
	{
		ft_error("could not execute command", cmd[0]);
		ft_free(command);
		return (ERROR);
	}
	ft_free(command);
	exit(EXIT_SUCCESS);
	return (OK);
}

static int	first_process(char *filename, char **cmd, char **envp, int next[])
{
	int	infile;

	infile = open(filename, O_RDONLY);
	if (infile == ERROR) 
		return (ft_error(NULL, filename));
	close(next[READ]);
	dup2(infile, STDIN_FILENO);
	dup2(next[WRITE], STDOUT_FILENO);
	close(next[WRITE]);
	if (ft_strlen(cmd[0]) < 1)
		cmd[0] = "cat";
	return (execute_command(cmd, envp));
}

static int	middle_process(char **cmd, char **envp, int prev[], int next[])
{
	close(prev[WRITE]);
	close(next[READ]);
	dup2(prev[READ], STDIN_FILENO);
	dup2(next[WRITE], STDOUT_FILENO);
	close(prev[READ]);
	close(next[WRITE]);
	if (ft_strlen(cmd[0]) < 1)
		return (ft_error(NULL, "command cannot be empty"));
	return (execute_command(cmd, envp));
}

static int	last_process(char *filename, char **cmd, char **envp, int prev[])
{
	int	outfile;

	outfile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == ERROR)
		return (ft_error(NULL, filename));
	close(prev[WRITE]);
	dup2(prev[READ], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(prev[READ]);
	if (ft_strlen(cmd[0]) < 1)
		cmd[0] = "cat";
	return (execute_command(cmd, envp));
}

int	pipex(int n, char **cmds, char **files, char **envp)
{
	int	i;
	int	prev[2];
	int	next[2];

	if (pipe(prev) == ERROR || pipe(next) == ERROR)
		return (ft_error(NULL, "failed to create pipeline"));
	if (fork() == OK)
		first_process(files[0], &cmds[0], envp, next);
	ft_copy_pipe(prev, next);
	i = 0;
	while (++i < n - 1)
	{
		if (pipe(next) == ERROR) 
			return (ft_error(NULL, "failed to create pipeline"));
		if (fork() == OK)
			middle_process(&cmds[i], envp, prev, next);
		ft_close_pipe(prev);
		ft_copy_pipe(prev, next);
	}
	ft_copy_pipe(prev, next);
	if (fork() == OK)
		last_process(files[1], &cmds[n - 1], envp, prev);
	ft_close_pipe(prev);
	ft_close_pipe(next);
	return (OK);
}
