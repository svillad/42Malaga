/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 13:09:08 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/09 15:49:29 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_doble_ptr(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
	*ptr = NULL;
	return (NULL);
}

static char	*find_cmd_path(char *cmd, char **envp)
{
	char	**paths;
	char	*end_path;
	char	*cmd_path;
	int		i;

	i = 0;
	end_path = ft_strjoin("/", cmd);
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", 5))
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], end_path);
		if (access(cmd_path, X_OK) == OK)
		{
			free(end_path);
			ft_free_doble_ptr(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(end_path);
	ft_free_doble_ptr(paths);
	return (NULL);
}

int	ft_execute_command(char **cmd, char **envp)
{
	char	**command;
	char	*path;

	command = ft_split(cmd[0], ' ');
	if (!command[0])
	{
		ft_error("parse error", "command cannot be empty");
		return (ERROR);
	}
	path = find_cmd_path(command[0], envp);
	if (!path)
	{
		ft_free_doble_ptr(command);
		ft_error("command not found", cmd[0]);
		return (ERROR);
	}
	if (execve(path, command, envp) == ERROR)
	{
		ft_free_doble_ptr(command);
		ft_error("could not execute command", cmd[0]);
		return (ERROR);
	}
	ft_free_doble_ptr(command);
	exit(EXIT_SUCCESS);
	return (OK);
}
