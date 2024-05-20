/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:31 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 19:45:16 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animation(void *param)
{
	t_game			*game;

	game = param;
	game->player.time++;
	if (game->win)
	{
		if (game->player.time == 200)
			mlx_close_window(game->mlx);
		return ;
	}
	if (game->player.time == ANIMATION_TIME)
	{
		game->player.time = 0;
		move_player(game, 0, 0, STOP);
	}
}

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
	{
		if (map->value[i] && map->value[i])
			free(map->value[i]);
	}
	if (map->value)
		free(map->value);
	map->value = NULL;
	map->height = 0;
	map->width = 0;
	map->capacity = 0;
}

void	end_game(t_game *game)
{
	int	j;

	if (game && game->map.value)
	{
		delete_player(game);
		delete_all_coins(game);
		mlx_delete_image(game->mlx, game->bg.img);
		mlx_delete_texture(game->bg.texture);
		j = -1;
		while (++j < 2)
		{
			mlx_delete_image(game->mlx, game->wall[j].img);
			mlx_delete_texture(game->wall[j].texture);
		}
		mlx_delete_image(game->mlx, game->exit.img);
		mlx_delete_texture(game->exit.texture);
		free_map(&game->map);
	}
}

void	ft_error_map(t_map *map, const char *message)
{
	ft_fprintf(STDERR_FILENO, "❌Error❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		ft_fprintf(STDERR_FILENO, "► %s\n", message);
	if (map && map->value)
		free_map(map);
	exit(EXIT_FAILURE);
}
