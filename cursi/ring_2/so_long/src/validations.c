/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:38 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 12:07:08 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	valid_columns_sizes(t_map *map)
{
	int	i;

	if (map->height < 3)
		ft_error_map(map, "invalid map size");
	i = 0;
	while (++i < map->height)
	{
		if (ft_strlen(map->value[i]) != strlen(map->value[i - 1]))
			ft_error_map(map, "invalid columns size");
	}
}

void	valid_characters(t_map *map)
{
	const char	*valid_chars;
	int			i;
	int			j;

	valid_chars = "01PCE";
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->value[i][j] != '\0')
		{
			if (ft_strchr(valid_chars, map->value[i][j]) == NULL)
			{
				ft_error_map(map, "invalid characters");
			}
			j++;
		}
		i++;
	}
}

void	valid_borders(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
	{
		if (map->value[i][0] != '1' || map->value[i][map->width - 1] != '1')
			ft_error_map(map, "invalid borders");
	}
	i = -1;
	while (++i < map->width)
	{
		if (map->value[0][i] != '1' || map->value[map->height - 1][i] != '1')
			ft_error_map(map, "invalid borders");
	}
}

void	valid_elements_quantity(t_map *map)
{
	int	counters[3];
	int	i;
	int	j;

	i = -1;
	counters[0] = 0;
	counters[1] = 0;
	counters[2] = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->value[i][j] == 'C')
				counters[0]++;
			else if (map->value[i][j] == 'P')
				counters[1]++;
			else if (map->value[i][j] == 'E')
				counters[2]++;
		}
	}
	if (counters[0] < 1 || counters[1] != 1 || counters[2] != 1)
		ft_error_map(map, "invalid elements quantity");
}

void	validate_map(t_map *map)
{
	valid_columns_sizes(map);
	valid_characters(map);
	valid_borders(map);
	valid_elements_quantity(map);
}
