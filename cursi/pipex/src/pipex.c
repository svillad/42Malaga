/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/02/24 20:47:00 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent_process(char **argv, char **envp, int *fd)
{
	int		output_file;

	output_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC);
	if (output_file == -1)
		error("Could not open <file2>");
	dup2(fd[0], STDIN_FILENO);
	dup2(output_file, STDOUT_FILENO);
	execute(argv[3], envp);
	close(fd[1]);
}

void	child_process(char **argv, char **envp, int *fd)
{
	int		input_file;

	input_file = open(argv[1], O_RDONLY);
	if (input_file == -1)
		error("Could not open <file1>");
	dup2(input_file, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	execute(argv[2], envp);
	close(fd[0]);
}
