/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:32:09 by svilla-d          #+#    #+#             */
/*   Updated: 2023/12/11 00:09:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*data[MAX_FILES];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!data[fd] || (data[fd] && !ft_strchr(data[fd], '\n')))
		data[fd] = ft_read_buffer(fd, data[fd]);
	if (!data[fd])
		return (NULL);
	line = ft_new_line(data[fd]);
	if (!line)
		return (ft_free(&data[fd]));
	data[fd] = ft_clear_data(data[fd], ft_strlen(data[fd]));
	return (line);
}

char	*ft_read_buffer(int fd, char *str)
{
	char	*buffer;
	int		num_chars;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&str));
	buffer[0] = '\0';
	num_chars = 1;
	while (num_chars > 0 && !ft_strchr(buffer, '\n'))
	{
		num_chars = read(fd, buffer, BUFFER_SIZE);
		if (num_chars > 0)
		{
			buffer[num_chars] = '\0';
			str = ft_strjoin(str, buffer);
		}
	}
	free(buffer);
	if (num_chars == -1)
		return (ft_free(&str));
	return (str);
}

char	*ft_new_line(char *str)
{
	char	*line;
	int		len;

	len = ft_strchr(str, '\n') - str + 1;
	if (len <= 0) 
		len = ft_strchr(str, '\0') - str + 1;
	line = ft_substr(str, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_clear_data(char *str, size_t len)
{
	char	*new_data;
	int		pos_n;

	pos_n = ft_strchr(str, '\n') - str + 1;
	if (pos_n < 0 || !str[pos_n])
		return (ft_free(&str));
	new_data = ft_substr(str, pos_n, len - pos_n);
	ft_free(&str);
	if (!new_data)
		return (NULL);
	return (new_data);
}
