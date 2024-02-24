/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:01:39 by svilla-d          #+#    #+#             */
/*   Updated: 2024/02/24 20:16:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;

	if (argc != 5)
	{
		error("Number of arguments is incorrect\n"
			"Ex: ./pipex <file1> <cmd1> <cmd2> <file2>");
		return (1);
	}
	if (pipe(fd) == -1)
		error("Failed to create pipeline");
	pid1 = fork();
	if (pid1 == -1)
		error("Could not create thread");
	if (pid1 == 0)
		child_process(argv, envp, fd);
	waitpid(pid1, NULL, 0);
	parent_process(argv, envp, fd);
	return (0);
}
