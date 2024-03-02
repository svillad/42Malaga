/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 18:51:25 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/02 20:26:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# define OK 0
# define BAD -1

/**
 * @brief This function is responsible for executing the child process that run
 *        inside a fork: take the inputFile, put the output inside a pipe
 * @param argv (char **): Array of strings containing the command-line arguments.
 * @param envp (char **): Array of strings containing the environment variables.
 * @param fd (int *): File descriptors for communication between processes.
 * @return void
 * @author Sebastian Villa
 */
void	child_process(char **argv, char **envp, int *fd);
/**
 * @brief This function is responsible for executing the parent process that take
 *        the data from the pipe, change the output for the outputFile
 * @param argv (char **): Array of strings containing the command-line arguments.
 * @param envp (char **): Array of strings containing the environment variables.
 * @param fd (int *): File descriptors for communication between processes.
 * @return void
 * @author Sebastian Villa
 */
void	parent_process(char **argv, char **envp, int *fd);
/**
 * @brief This function is responsible for handling errors in the pipex program.
 * @return message (const char *) Error message
 * @author Sebastian Villa
 */
void	ft_error(const char *error, const char *message);
/**
 * @brief This function is responsible for finding the path of a command in the
 *        environment variables.
 * @param cmd (char *): Command to find the path for.
 * @param envp (char **): Array of strings containing the environment variables.
 * @return A string containing the path of the command if found, otherwise NULL.
 * @author Sebastian Villa
 */
char	*ft_find_cmd_path(char *cmd, char **envp);
/**
 * @brief This function is responsible for reading the next line from a file
 *        descriptor.
 * @param line (char **): Pointer to a string where the read line will be stored.
 * @return 1 if a line has been read successfully, 0 if the end of the file has
 *         been reached, -1 on error.
 * @author Sebastian Villa
 */
int		get_next_line(char **line);
/**
 * @brief This function is responsible for executing a command with the given
 *        arguments.
 * @param argv (char *): Command to execute.
 * @param envp (char **): Array of strings containing the environment variables.
 * @return void
 * @author Sebastian Villa
 */
// void	execute(char *path, char **cmd, char **envp);
void	ft_free(char **ptr);

#endif