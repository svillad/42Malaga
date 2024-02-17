/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:01:39 by svilla-d          #+#    #+#             */
/*   Updated: 2024/02/17 20:18:44 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipeFd[2];
	pid_t	pid1;

	if (argc != 5)
	{
		ft_printf("\e[31mERROR: number of arguments is incorrect\n\e[0m", 2);
		ft_printf("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
		return (1);
	}
	if (pipe(pipeFd) == -1)
		error();
	pid1 = fork();
	if (pid1 == -1)
		error();
	if (pid1 == 0)
		child_process(argv, envp, pipeFd);
	waitpid(pid1, NULL, 0);
	parent_process(argv, envp, pipeFd);
	return (0);
}
