/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:26 by svilla-d          #+#    #+#             */
/*   Updated: 2024/06/19 11:35:27 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(const char *error, const char *message)
{
	if (message == NULL || ft_strlen(message) == 0)
		perror("Error");
	else if (error == NULL)
		ft_fprintf(STDERR_FILENO, "zsh: %s: %s\n", strerror(errno),
			message);
	else
		ft_fprintf(STDERR_FILENO, "zsh: %s: %s\n", error, message);
	exit(EXIT_FAILURE);
	return (ERROR);
}

void	ft_copy_pipe(int dst[], int src[])
{
	dst[READ] = src[READ];
	dst[WRITE] = src[WRITE];
}

void	ft_free_str(char *str)
{
	if (!str)
		free(str);
}

void	write_pipe(int temp[], char *input)
{
	if (write(temp[WRITE], input, ft_strlen(input)) == ERROR)
	{
		ft_free_str(input);
		ft_error(NULL, "pipex: temp write");
	}
	ft_free_str(input);
}

void	ft_read_stdin(int temp[], char **files, char *input)
{
	char	*line;
	char	*temp_input;

	input = NULL;
	while (1)
	{
		ft_putstr_fd(files[MSG], STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line && ft_strncmp(line, files[LIM], strlen(files[LIM])) == OK)
			break ;
		if (line && input)
		{
			temp_input = ft_strdup(input);
			ft_free_str(input);
			input = ft_strjoin(temp_input, line);
			ft_free_str(temp_input);
		}
		else if (line)
			input = ft_strdup(line);
		ft_free_str(line);
	}
	write_pipe(temp, input);
	exit(EXIT_SUCCESS);
}
