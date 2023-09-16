/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:17:21 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:17:23 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_file.h"

char	*ft_read_file(char *file_name)
{
	int		file;
	char	buffer[BUFFER_SIZE];
	char	*content;
	int		len;
	int		i;

	file = open(file_name, O_RDONLY);
	if (file == -1)
		return (NULL);
	len = read(file, buffer, BUFFER_SIZE);
	if (len == -1)
	{
		close(file);
		return (NULL);
	}
	content = (char *)malloc((len + 1) * sizeof(char));
	if (!content)
		return (NULL);
	i = -1;
	while (++i < len)
		content[i] = buffer[i];
	content[i] = '\0';
	if (close(file) == -1)
		return (NULL);
	return (content);
}
