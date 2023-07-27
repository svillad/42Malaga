/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereca-ca <ereca-ca@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 12:18:39 by ereca-ca          #+#    #+#             */
/*   Updated: 2023/07/27 12:18:42 by ereca-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.h"

void	ft_free_row(char **map)
{
	int	j;

	j = 0;
	while (map[j])
	{
		free(map[j]);
		j++;
	}
	free(map);
}

char	**ft_init_map(int rows, char *info, char *line1)
{
	int		i;
	int		j;
	int		col_ref;
	char	**map;

	map = (char **)malloc((rows + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	j = -1;
	col_ref = ft_get_row_size(&info[0]);
	while (++j < rows && info[i])
	{
		map[j] = ft_get_line(col_ref, &info[i], line1);
		if (!map[j])
			return (NULL);
		i += col_ref;
	}
	if (j != rows)
	{
		ft_free_row(map);
		return (NULL);
	}
	map[j] = NULL;
	return (map);
}

char	*ft_get_line(int col_ref, char *info, char *line1)
{
	int		col;
	char	*line;

	col = ft_get_row_size(info);
	if (col != col_ref)
	{
		return (NULL);
	}
	line = (char *)malloc(col * sizeof(char));
	if (!line)
		return (NULL);
	if (ft_copy_line(line, info, line1) < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	**ft_process_map(char **map, int rows, int cols, char cobst)
{
	int	i;
	int	j;
	int	**m;

	m = (int **)malloc(rows * sizeof(int *));
	if (!m)
		return (NULL);
	i = -1;
	while (map[++i] != NULL)
	{
		m[i] = (int *)malloc(cols * sizeof(int));
		if (!m[i])
			return (NULL);
		j = -1;
		while (map[i][++j])
		{
			if ((i == 0 || j == 0) && map[i][j] != cobst)
				m[i][j] = 1;
			else if (map[i][j] == cobst)
				m[i][j] = 0;
			else
				m[i][j] = ft_min(m[i - 1][j], m[i][j - 1], m[i - 1][j - 1]) + 1;
		}
	}
	return (m);
}

int	ft_copy_line(char *dest, char *src, char *line1)
{
	int	i;
	int	n;

	i = 0;
	n = ft_strlen(line1);
	while (src[i] && src[i] != '\n')
	{
		if (src[i] != line1[n - 2] && src[i] != line1[n - 3])
			return (-2);
		dest[i] = src[i];
		i++;
	}
	if (src[0] == '\n')
		return (-2);
	dest[i] = '\0';
	return (0);
}
