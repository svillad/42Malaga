/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/07 17:44:55 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	here_doc(char **files, char **cmd, char **envp, int next[])
{
	pid_t	pid;
	int		temp[2];
	char	*input;

	input = NULL;
	if (pipe(temp) == ERROR)
		return (ft_error(NULL, "failed to create pipeline"));
	pid = fork();
	if (pid == 0)
		ft_read_stdin(temp, files, input);
	waitpid(pid, NULL, 0);
	close(temp[WRITE]);
	close(next[READ]);
	dup2(temp[READ], STDIN_FILENO);
	dup2(next[WRITE], STDOUT_FILENO);
	close(temp[READ]);
	close(next[WRITE]);
	ft_free_str(input);
	if (ft_strlen(cmd[0]) < 1)
		return (ft_error(NULL, "command cannot be empty"));
	ft_execute_command(cmd, envp);
	return (OK);
}

static int	first_process(char **files, char **cmd, char **envp, int next[])
{
	int	infile;

	if (files[IN])
	{
		infile = open(files[IN], O_RDONLY);
		if (infile == ERROR) 
			return (ft_error(NULL, files[IN]));
		close(next[READ]);
		dup2(infile, STDIN_FILENO);
		dup2(next[WRITE], STDOUT_FILENO);
		close(infile); 
		if (ft_strlen(cmd[0]) < 1)
			cmd[0] = "cat";
		ft_execute_command(cmd, envp);
	}
	else
		here_doc(files, cmd, envp, next);
	return (OK);
}

static int	middle_process(char **cmd, char **envp, int prev[])
{
	pid_t	pid;
	int		status;
	int		next[2];

	if (pipe(next) == ERROR)
		return (ft_error(NULL, "failed to create pipeline"));
	pid = fork();
	if (pid == 0)
	{
		close(prev[WRITE]);
		close(next[READ]);
		dup2(prev[READ], STDIN_FILENO);
		dup2(next[WRITE], STDOUT_FILENO);
		close(prev[READ]);
		close(next[WRITE]);
		if (ft_strlen(cmd[0]) < 1)
			return (ft_error(NULL, "command cannot be empty"));
		ft_execute_command(cmd, envp);
	}
	close(next[WRITE]);
	waitpid(pid, &status, 0);
	ft_copy_pipe(prev, next);
	return (status);
}

static int	last_process(char **files, char **cmd, char **envp, int prev[])
{
	int	outfile;

	if (files[IN])
		outfile = open(files[OUT], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		outfile = open(files[OUT], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == ERROR)
		return (ft_error(NULL, files[OUT]));
	dup2(outfile, STDOUT_FILENO);
	close(prev[WRITE]);
	dup2(prev[READ], STDIN_FILENO);
	close(outfile);
	close(prev[READ]);
	if (ft_strlen(cmd[0]) < 1)
		cmd[0] = "cat";
	ft_execute_command(cmd, envp);
	return (OK);
}

int	pipex(int n, char **cmds, char **files, char **envp)
{
	pid_t	pid;
	int		i;
	int		pipe_fd[2];
	int		status;
	int		final_status;

	if (pipe(pipe_fd) == ERROR)
		return (ft_error(NULL, "failed to create pipeline"));
	pid = fork();
	if (pid == 0)
		first_process(files, &cmds[0], envp, pipe_fd);
	waitpid(pid, &status, 0);
	final_status = status;
	close(pipe_fd[WRITE]);
	i = 0;
	while (++i < n - 1)
		final_status += middle_process(&cmds[i], envp, pipe_fd);
	pid = fork();
	if (pid == 0)
		last_process(files, &cmds[n - 1], envp, pipe_fd);
	waitpid(pid, &status, 0);
	final_status += status;
	return (final_status);
}
