/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:25 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/07 13:20:43 by svilla-d         ###   ########.fr       */
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
# define LIM 2
# define MSG 3

/**
 * @brief This function is responsible for handling errors in the pipex program.
 * @param error (const char *): error type.
 * @param message (const char *): error message.
 * @return (integer with ERROR value);
 * @author Sebastian Villa
 */
int		ft_error(const char *error, const char *message);
/**
 * @brief This function executes a command with given arguments and environment
 * 		variables.
 * @param cmd (char **): Array of strings containing the commands.
 * @param envp (char **): Array of strings containing the environment variables.
 * @return Returns 0 upon successful execution; otherwise, returns -1.
 */
int		ft_execute_command(char **cmd, char **envp);
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
 * @brief This function copies the contents of one pipe to another.
 * This function copies the file descriptors of one pipe (`src`) to another pipe
 * (`dst`).
 * @param dst (int[]): Destination array to copy file descriptors to.
 * @param src (int[]): Source array to copy file descriptors from.
 */
/**
 * @brief This function copies the contents of one pipe to another.
 * This function copies the file descriptors of one pipe (`src`) to another pipe
 * (`dst`).
 * @param dst (int[]): Destination array to copy file descriptors to.
 * @param src (int[]): Source array to copy file descriptors from.
 */
void	ft_copy_pipe(int dst[], int src[]);
/**
 * @brief This function frees memory allocated for a string.
 * @param str (char *): String to free memory for.
 */
void	ft_free_str(char *str);
/**
 * @brief This function reads from standard input and stores it in a buffer.
 * @param temp (int[]): Array representing file descriptors for communication.
 * @param files (char **): Array of strings specifying input and output files.
 * @param input (char *): Buffer to store the input read from standard input.
 */
void	ft_read_stdin(int temp[], char **files, char *input);

#endif