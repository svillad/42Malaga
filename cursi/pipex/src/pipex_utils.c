/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:26 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/07 13:13:11 by svilla-d         ###   ########.fr       */
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

void	ft_read_stdin(int temp[], char **files, char *input)
{
	char	buffer[BUFFER_SIZE];
	char	*temp_input;
	ssize_t	bytes;

	input = NULL;
	while (1)
	{
		ft_putstr_fd(files[MSG], STDOUT_FILENO);
		bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
		if (bytes == ERROR)
		{
			ft_free_str(input);
			ft_error(NULL, "could not read data");
		}
		if (bytes == 0 || strncmp(buffer, files[LIM], strlen(files[LIM])) == OK)
			break ;
		if (input)
		{
			temp_input = ft_strdup(input);
			ft_free_str(input);
			input = ft_strjoin(temp_input, buffer);
			ft_free_str(temp_input);
		}
		else
			input = ft_strdup(buffer);
	}
	if (write(temp[WRITE], input, ft_strlen(input)) == ERROR)
	{
		ft_free_str(input);
		ft_error(NULL, "pipex: temp write");
	}
	exit(EXIT_SUCCESS);
}
