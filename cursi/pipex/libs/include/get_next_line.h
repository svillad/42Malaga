/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:32:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/03/06 11:54:58 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# define MAX_FILES 4096

/**
 * @brief Reads a line from a file descriptor.
 * @param fd (int): File descriptor from which to read.
 * @return The line read from the file descriptor, or NULL if an error occurs or
 *         if the end of the file is reached.
 * @author Sebastian Villa
 */
char	*get_next_line(int fd);
/**
 * @brief Reads a buffer from a file descriptor.
 * @param fd (int): File descriptor from which to read.
 * @param str (char *): Buffer where the read data will be stored.
 * @return The buffer with the data read from the file descriptor.
 * @author Sebastian Villa
 */
char	*ft_read_buffer(int fd, char *str);
/**
 * @brief Finds the next line in a string.
 * @param str (char *): String in which to find the next line.
 * @return A pointer to the next line in the string, or NULL if no newline
 *         character is found.
 * @author Sebastian Villa
 */
char	*ft_new_line(char *str);
/**
 * @brief Frees the memory allocated for a string and sets its pointer to NULL.
 * @param ptr (char **): Pointer to the string to free.
 * @return NULL to assign to the pointer after freeing the memory.
 * @author Sebastian Villa
 */
char	*ft_free(char **ptr);
/**
 * @brief Deletes the used line from a string.
 * @param str (char *): String from which to delete the used line.
 * @param len (size_t): Length of the used line to delete.
 * @return A pointer to the modified string after deleting the used line.
 * @author Sebastian Villa
 */
char	*ft_delete_used_line(char *str, size_t len);
/**
 * @brief Joins two strings, allocating memory for the result.
 * @param s1 (char *): First string.
 * @param s2 (char *): Second string.
 * @return A pointer to the newly allocated memory containing the concatenated
 *         string, or NULL if the allocation fails. The caller is responsible for
 *         freeing the memory allocated.
 * @author Sebastian Villa
 */
char	*ft_strjoin_next(char *s1, char *s2);

#endif