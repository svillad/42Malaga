/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:25 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/06 20:01:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define OK 0
# define ERROR -1
# define READ 0
# define WRITE 1
# define IN 0
# define OUT 1
# define LIMITER 2

/**
 * @brief This function is responsible for handling errors in the pipex program.
 * @param error (const char *): error type.
 * @param message (const char *): error message.
 * @return (integer with ERROR value);
 * @author Sebastian Villa
 */
int		ft_error(const char *error, const char *message);
/**
 * @brief This function is responsible for finding the path of a command in the
 *        environment variables. This function searches for the executable file
 * corresponding to the given command in the directories specified by the PATH
 * environment variable. If the command is found, its absolute path is returned;
 * otherwise, NULL is returned.
 * @param cmd (char *): Command to find the path for.
 * @param envp (char **): Array of strings containing the environment variables.
 * @return A string containing the path of the command if found, otherwise NULL.
 * @author Sebastian Villa
 */
char	*ft_find_cmd_path(char *cmd, char **envp);
/**
 * @brief This function frees memory allocated for an array of strings.
 * This function iterates through the array of strings pointed to by `ptr` and
 * frees the memory allocated for each string. It then frees the memory allocated
 * for the array itself.
 * @param ptr (char **): Pointer to the array of strings to free.
 */
// void	ft_free(char **ptr);
/**
 * @brief This function performs the pipelining process.
 * This function sets up a pipeline using the commands specified in `cmds`, with
 * input redirected from `files[0]` and output redirected to `files[1]`. The
 * `envp` parameter provides the environment variables for the commands. The
 * number of commands is specified by `n`.
 * @param n (int): Number of commands in the pipeline.
 * @param cmds (char **): Array of strings containing the commands to execute.
 * @param files (char **): Array of strings specifying input and output files.
 * @param envp (char **): Array of strings containing the environment variables.
 * @return Returns 0 upon successful execution; otherwise,returns -1.
 */
int		pipex(int n, char **cmds, char **files, char **envp);
/**
 * @brief This function closes both ends of a pipe.
 * This function closes both the read and write ends of the pipe specified by
 * `pipe_fd`.
 * @param pipe_fd (int[]): Array containing file descriptors for the pipe.
 */
void	ft_close_pipe(int pipe_fd[]);
/**
 * @brief This function copies the contents of one pipe to another.
 * This function copies the file descriptors of one pipe (`src`) to another pipe
 * (`dst`).
 * @param dst (int[]): Destination array to copy file descriptors to.
 * @param src (int[]): Source array to copy file descriptors from.
 */
void	ft_copy_pipe(int dst[], int src[]);
#endif