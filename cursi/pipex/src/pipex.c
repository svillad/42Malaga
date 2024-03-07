/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 19:02:15 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/07 11:45:34 by svilla-d         ###   ########.fr       */
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
		ft_free(command);
		ft_error("command not found", cmd[0]);
		return (ERROR);
	}
	if (execve(path, command, envp) == ERROR)
	{		
		ft_free(command);
		ft_error("could not execute command", cmd[0]);
		return (ERROR);
	}
	ft_free(command);
	exit(EXIT_SUCCESS);
	return (OK);
}

void	ft_free_str(char *str)
{
	if(!str)
		free(str);
}

int read_input(int temp[], char **files, char *msg)
{
	char buffer[BUFFER_SIZE];
	char *input;
	char *temp_input;
    ssize_t bytes_read = 0;

	input = NULL;
    while (1) {
        ft_putstr_fd(msg, STDOUT_FILENO);
		bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read == -1) {
			ft_free_str(input);
            ft_error(NULL, "could not read data");
            return ERROR;
        }
        if (bytes_read == 0 || strncmp(buffer, files[LIM], strlen(files[LIM])) == 0) {
            break;
        }
		if (input)
		{
			temp_input = ft_strdup(input);
			ft_free_str(input);
			input = ft_strjoin(temp_input, buffer);
			ft_free_str(temp_input);
		} else {
			input = ft_strdup(buffer);
		}
    }
	if (write(temp[WRITE], input, ft_strlen(input)) == -1) {
		ft_free_str(input);
	    return ft_error(NULL, "pipex: temp write");
	}
	ft_free_str(input);
	exit(EXIT_SUCCESS);
    return OK;
}

static int here_doc(int n, char **files, char **cmd, char **envp, int next[])
{
    pid_t pid;
	int temp[2];
	char *msg;

	msg = "heredoc> ";
    if (pipe(temp) == ERROR) {
		return (ft_error(NULL, "failed to create pipeline"));
	}
	if ((pid = fork()) == ERROR) {
		return (ft_error(NULL, "failed to fork"));
	} else if (pid == 0) {
		if (n > 1)
			msg = "pipe heredoc> ";
		read_input(temp, files, msg);
	}
	waitpid(pid, NULL, 0);
	close(temp[WRITE]);
	close(next[READ]);
	dup2(temp[READ], STDIN_FILENO);
	dup2(next[WRITE], STDOUT_FILENO);
	close(temp[READ]);
	close(next[WRITE]);
	if (ft_strlen(cmd[0]) < 1)
		return (ft_error(NULL, "command cannot be empty"));
	execute_command(cmd, envp);
	return (OK);
}

static int	first_process(int n, char **files, char **cmd, char **envp, int next[])
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
		execute_command(cmd, envp);
	}
	else
	{	
		here_doc(n, files, cmd, envp, next);
	}
	return 0;
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
	execute_command(cmd, envp);
	return 0;
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
        first_process(n, files, &cmds[0], envp, next);
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
