/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/07 00:44:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	print_data(int fd)
// {
// 	char	buffer[256];
// 	ssize_t	bytes_read;
// 	write(STDOUT_FILENO, "---------\n", 10);
// 	bytes_read = read(fd, buffer, 256);
// 	write(STDOUT_FILENO, buffer, bytes_read);
// }

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
		exit(EXIT_FAILURE);
		return (ERROR);
	}
	ft_free(command);
	exit(EXIT_SUCCESS);
	return (OK);
}

int here_doc(int next[], char **files) {
    char buffer[BUFFER_SIZE];
	char *input = "";
    ssize_t bytes_read = 0;

    while (1) {
        ft_putstr_fd("heredoc> ", STDOUT_FILENO);
        while(buffer[bytes_read - 1] != '\n')
            bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (strncmp(buffer, files[LIMITER], strlen(files[LIMITER])) == 0) {
            break;
        }
		input = ft_strjoin(input, buffer);
		bytes_read = 0;
    }
	if (write(next[WRITE], input, ft_strlen(input)) == -1) {
	    return ft_error(NULL, "pipex: write");
	}
    return 1;
}

static int	first_process(char **files, char **cmd, char **envp, int next[])
{
	printf("0) CMD:%s\n", cmd[0]);
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
		execute_command(cmd, envp);
	}
	else
	{	
		// print_data(next[READ]);
		close(next[READ]);
		here_doc(next, files);
		// execute_command(cmd, envp);
	}
	return 0;
}

static int	middle_process(char **cmd, char **envp, int prev[], int next[])
{
	printf(" *) CMD:%s\n", cmd[0]);

	close(prev[WRITE]);
	close(next[READ]);
	dup2(prev[READ], STDIN_FILENO);
	dup2(next[WRITE], STDOUT_FILENO);
	close(prev[READ]);
	close(next[WRITE]);
	if (ft_strlen(cmd[0]) < 1)
		return (ft_error(NULL, "command cannot be empty"));
	execute_command(cmd, envp);
	return 0;
}

static int	last_process(char **files, char **cmd, char **envp, int prev[])
{
	// printf("%d) CMD:%s\n", i, cmd[0]);
	int	outfile;

	outfile = open(files[OUT], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == ERROR)
		return (ft_error(NULL, files[OUT]));
    dup2(outfile, STDOUT_FILENO);
    close(prev[WRITE]);
    dup2(prev[READ], STDIN_FILENO);
    close(outfile);
    close(prev[READ]);
	if (ft_strlen(cmd[0]) < 1)
		cmd[0] = "cat";
	execute_command(cmd, envp);
	return 0;
}
int pipex(int n, char **cmds, char **files, char **envp) {
    int i;
    int prev[2];
    int next[2];
    pid_t pid;

    if (pipe(prev) == ERROR || pipe(next) == ERROR)
        return (ft_error(NULL, "failed to create pipeline"));
    if ((pid = fork()) == ERROR) {
        return (ft_error(NULL, "failed to fork"));
    } else if (pid == 0) {
        first_process(files, &cmds[0], envp, next);
    }
	waitpid(pid, NULL, 0);
	close(next[WRITE]);
	ft_copy_pipe(prev, next);

    for (i = 1; i < n - 1; ++i) {
        if (pipe(next) == ERROR) {
            return (ft_error(NULL, "failed to create pipeline"));
        }
        if ((pid = fork()) == ERROR) {
            return (ft_error(NULL, "failed to fork"));
        } else if (pid == 0) {
            middle_process(&cmds[i], envp, prev, next);
        }
		waitpid(pid, NULL, 0);
		close(next[WRITE]);
        ft_copy_pipe(prev, next);
    }	
    if ((pid = fork()) == ERROR) {
        return (ft_error(NULL, "failed to fork"));
    } else if (pid == 0) {
        last_process(files, &cmds[n - 1], envp, prev);
    }
	waitpid(pid,NULL,0);
    close(prev[READ]);
    return OK;
}
