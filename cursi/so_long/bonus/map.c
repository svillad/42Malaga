/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:21 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 16:36:59 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	check_extension(t_map *map)
{
	int			len;
	const char	*name;

	name = map->name;
	len = ft_strlen(name);
	if (len < 5)
		ft_error_map(map, "invalid file extension");
	if (name[len - 4] != '.' || name[len - 3] != 'b' || name[len - 2] != 'e'
		|| name[len - 1] != 'r')
		ft_error_map(map, "invalid file extension");
}

void	add_line(t_map *map, const char *line)
{
	int		new_capacity;
	char	**new_lines;
	int		i;

	if (map->height == map->capacity)
	{
		if (map->capacity == 0)
			new_capacity = 1;
		else
			new_capacity = map->capacity * 2;
		new_lines = (char **)malloc(new_capacity * sizeof(char *));
		if (new_lines == NULL)
			ft_error_map(map, "could not allocate memory");
		i = -1;
		while (++i < map->height)
			new_lines[i] = map->value[i];
		if (map->value)
			free(map->value);
		map->value = new_lines;
		map->capacity = new_capacity;
	}
	map->value[map->height] = ft_strtrim(line, "\n");
	if (map->value[map->height] == NULL)
		ft_error_map(map, "could not allocate memory");
	map->height++;
}

void	print_map(t_map *map)
{
	int	i;

	i = -1;
	ft_printf("h:%d w:%d c:%d\n", map->height, map->width, map->capacity);
	while (++i < map->height)
		ft_printf("%s\n", map->value[i]);
	ft_printf("\n");
}

void	read_map(t_map *map, char *path)
{
	int		fd;
	char	*line;

	map->value = NULL;
	map->name = path;
	map->height = 0;
	map->width = 0;
	map->capacity = 0;
	check_extension(map);
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		ft_error_map(NULL, "could not open the file");
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map->width = ft_strlen(line);
		add_line(map, line);
		if (line)
			free(line);
	}
	close(fd);
	validate_map(map);
}
