/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:27:08 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 11:54:28 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(t_game *game)
{
	char	**copy_map;
	int		i;

	copy_map = (char **)malloc(sizeof(char *) * game->map.height + 1);
	if (!copy_map)
		return (NULL);
	i = -1;
	while (++i < game->map.height)
	{
		copy_map[i] = ft_strdup(game->map.value[i]);
		if (!copy_map[i])
		{
			ft_free_double_ptr(copy_map);
			return (NULL);
		}
	}
	copy_map[i] = NULL;
	return (copy_map);
}

static bool	floodfill(char **map, t_game game, int x, int y)
{
	static bool	exit = false;
	static int	collect = 0;

	if (map[y][x] == '1' || map[y][x] == '*')
		return (false);
	if (game.map.value[y][x] == 'E')
		exit = true;
	if (game.map.value[y][x] == 'C')
		collect++;
	map[y][x] = '*';
	floodfill(map, game, x + 1, y);
	floodfill(map, game, x - 1, y);
	floodfill(map, game, x, y + 1);
	floodfill(map, game, x, y - 1);
	if (exit == true && game.total_coins == collect)
		return (true);
	else
		return (false);
}

void	validate_path(t_game *game)
{
	char	**map;

	map = copy_map(game);
	if (floodfill(map, *game, game->player.x, game->player.y) == false)
	{
		ft_free_double_ptr(map);
		ft_error_map(&game->map, "invalid path");
	}
	ft_free_double_ptr(map);
}
