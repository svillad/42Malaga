/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:30:02 by svilla-d          #+#    #+#             */
/*   Updated: 2023/12/14 19:45:23 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*data = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!data || (data && !ft_strchr(data, '\n')))
		data = ft_read_buffer(fd, data);
	if (!data)
		return (NULL);
	line = ft_new_line(data);
	if (!line)
		return (ft_free(&data));
	data = ft_delete_used_line(data, ft_strlen(data));
	return (line);
}

char	*ft_read_buffer(int fd, char *str)
{
	char	*buffer;
	int		num_chars;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
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

char	*ft_delete_used_line(char *str, size_t len)
{
	char	*new_data;
	char	*ptr_nl;
	int		pos_nl;

	ptr_nl = ft_strchr(str, '\n');
	if (!ptr_nl)
	{
		new_data = NULL;
		return (ft_free(&str));
	}
	pos_nl = ptr_nl - str + 1;
	if (pos_nl < 0 || !str[pos_nl])
		return (ft_free(&str));
	new_data = ft_substr(str, pos_nl, len - pos_nl);
	ft_free(&str);
	if (!new_data)
		return (NULL);
	return (new_data);
}
