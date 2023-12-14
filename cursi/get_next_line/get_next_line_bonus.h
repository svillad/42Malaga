/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:32:18 by svilla-d          #+#    #+#             */
/*   Updated: 2023/12/14 19:21:55 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif
# define MAX_FILES 4096

char	*get_next_line(int fd);
char	*ft_read_buffer(int fd, char *str);
char	*ft_new_line(char *str);
char	*ft_free(char **str);
char	*ft_delete_used_line(char *str, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(const char *str, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *str);

#endif