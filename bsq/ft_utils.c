/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:20:19 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:59:26 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_min(int a, int b, int c)
{
	int	minimum;

	minimum = a;
	if (b < minimum)
		minimum = b;
	if (c < minimum)
		minimum = c;
	return (minimum);
}

void	ft_free_memory(char **map, char *info, char *line1)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i] != NULL)
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
	if (info != NULL)
		free(info);
	if (line1 != NULL)
		free(line1);
}

char	*ft_strcpy(char *info, char *line1)
{
	int	i;

	i = 0;
	while (line1[i])
	{
		info[i] = line1[i];
		i++;
	}
	info[i] = '\0';
	return (info);
}
