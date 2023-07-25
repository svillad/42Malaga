/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxgarci <maxgarci@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:23:05 by maxgarci          #+#    #+#             */
/*   Updated: 2023/07/23 17:23:07 by maxgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

int	ft_count_lines(char *file_name)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	int		len;
	int		line;
	int		i;

	file = open(file_name, 0);
	if (file == -1)
		return (-1);
	line = 0;
	len = read(file, buffer, BUFFER_SIZE);
	if (len == -1)
	{
		close(file);
		return (-1);
	}
	i = -1;
	while (++i < len)
		if (buffer[i] == ':')
			line++;
	if (close(file) == -1)
		return (-1);
	return (line);
}

char	*ft_read_file(char *file_name, int *len)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	char	*content;
	int		i;

	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (NULL);
	*len = read(file, buffer, BUFFER_SIZE);
	if (*len == -1)
	{
		close(file);
		return (NULL);
	}
	content = (char *)malloc((*len) * sizeof(char));
	i = -1;
	while (++i < *len)
	{
		content[i] = buffer[i];
	}
	content[i] = '\0';
	if (close(file) == -1)
		return (NULL);
	return (content);
}
