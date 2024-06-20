/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:31 by svilla-d          #+#    #+#             */
/*   Updated: 2024/06/20 13:35:58 by svilla-d         ###   ########.fr       */
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
	if (map->name)
		free(map->name);
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
		if (game->bg.texture != NULL)
			mlx_delete_texture(game->bg.texture);
		mlx_delete_image(game->mlx, game->bg.img);
		j = -1;
		while (++j < 2)
		{
			if (game->wall[j].texture != NULL)
				mlx_delete_texture(game->wall[j].texture);
			mlx_delete_image(game->mlx, game->wall[j].img);
		}
		if (game->exit.texture != NULL)
			mlx_delete_texture(game->exit.texture);
		mlx_delete_image(game->mlx, game->exit.img);
		free_map(&game->map);
	}
	mlx_terminate(game->mlx);
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

void	ft_error_game(t_game *game, const char *message)
{
	ft_fprintf(STDERR_FILENO, "❌Error❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		ft_fprintf(STDERR_FILENO, "► %s\n", message);
	end_game(game);
	exit(EXIT_FAILURE);
}
