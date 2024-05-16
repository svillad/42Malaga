/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:38 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/17 00:43:11 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	valid_columns_sizes(t_map *map)
{
	int	i;

	ft_printf("* valid_columns_sizes *\n");
	if (map->height < 3)
		ft_error_map(map, "invalid map size");
	i = 0;
	while (++i < map->height)
	{
		if (ft_strlen(map->map[i]) != strlen(map->map[i - 1]))
			ft_error_map(map, "invalid columns size");
	}
}

void	valid_characters(t_map *map)
{
	const char	*valid_chars;
	int			i;
	int			j;

	ft_printf("* valid_characters *\n");
	valid_chars = "01PCE";
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (ft_strchr(valid_chars, map->map[i][j]) == NULL)
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

	ft_printf("* valid_borders *\n");
	i = -1;
	while (++i < map->height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->width - 1] != '1')
			ft_error_map(map, "invalid borders");
	}
	i = -1;
	while (++i < map->width)
	{
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			ft_error_map(map, "invalid borders");
	}
}

void	valid_elements_quantity(t_map *map)
{
	int	counters[3];
	int	i;
	int	j;

	ft_printf("* valid_elements_quantity *\n");
	i = -1;
	counters[0] = 0;
	counters[1] = 0;
	counters[2] = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->map[i][j] == 'C')
				counters[0]++;
			else if (map->map[i][j] == 'P')
				counters[1]++;
			else if (map->map[i][j] == 'E')
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
