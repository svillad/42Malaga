/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:26 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/02 20:45:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(const char *error, const char *message)
{
	if (message == NULL || ft_strlen(message) == 0)
		perror("Error");
	else if (error == NULL)
		ft_fprintf(STDERR_FILENO, "zsh: %s: %s\n", strerror(errno),
			message);
	else
		ft_fprintf(STDERR_FILENO, "zsh: %s: %s\n", error, message);
	exit(EXIT_FAILURE);
}

void	ft_free(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

char	*ft_find_cmd_path(char *cmd, char **envp)
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
			ft_free(paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(end_path);
	ft_free(paths);
	return (NULL);
}
