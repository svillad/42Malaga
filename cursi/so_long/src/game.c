/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:26:53 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 19:43:01 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_parameters(t_game *game)
{
	int	i;
	int	j;

	game->win = false;
	game->moves = 0;
	game->total_coins = 0;
	game->collected_coins = 0;
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (game->map.value[i][j] == 'C')
				game->total_coins++;
			if (game->map.value[i][j] == 'P')
			{
				game->player.y = i;
				game->player.x = j;
			}
		}
	}
}

void	load_images(t_game *game)
{
	srand(getpid());
	game->bg.texture = mlx_load_png("./textures/bg.png");
	game->bg.img = mlx_texture_to_image(game->mlx, game->bg.texture);
	game->wall[0].texture = mlx_load_png("./textures/rock.png");
	game->wall[0].img = mlx_texture_to_image(game->mlx, game->wall[0].texture);
	game->wall[1].texture = mlx_load_png("./textures/tree.png");
	game->wall[1].img = mlx_texture_to_image(game->mlx, game->wall[1].texture);
	game->exit.texture = mlx_load_png("./textures/kamehouse.png");
	game->exit.img = mlx_texture_to_image(game->mlx, game->exit.texture);
	load_coins(game);
}

void	draw_map(int i, int j, int *n_coin, t_game *game)
{
	mlx_image_to_window(game->mlx, game->bg.img, WIDTH * j, HEIGHT * i);
	if (game->map.value[i][j] == '1')
	{
		mlx_image_to_window(game->mlx, game->wall[rand() % 2].img, WIDTH * j,
			HEIGHT * i);
	}
	else if (game->map.value[i][j] == 'C')
	{
		mlx_image_to_window(game->mlx, game->coin[*n_coin].img, WIDTH * j,
			HEIGHT * i);
		(*n_coin)++;
	}
	else if (game->map.value[i][j] == 'E')
	{
		mlx_image_to_window(game->mlx, game->exit.img, WIDTH * j, HEIGHT * i);
	}
}

void	key_press_event(mlx_key_data_t keycode, void *param)
{
	t_game	*game;
	mlx_t	*mlx;

	game = param;
	if (!game->win)
	{
		mlx = game->mlx;
		if (keycode.action == MLX_PRESS)
		{
			if (keycode.key == MLX_KEY_ESCAPE)
				mlx_close_window(mlx);
			else if (keycode.key == MLX_KEY_UP || keycode.key == MLX_KEY_W)
				move_player(game, 0, -1, UP);
			else if (keycode.key == MLX_KEY_DOWN || keycode.key == MLX_KEY_S)
				move_player(game, 0, +1, DOWN);
			else if (keycode.key == MLX_KEY_LEFT || keycode.key == MLX_KEY_A)
				move_player(game, -1, 0, LEFT);
			else if (keycode.key == MLX_KEY_RIGHT || keycode.key == MLX_KEY_D)
				move_player(game, +1, 0, RIGHT);
			else if (keycode.key == MLX_KEY_SPACE)
				move_player(game, 0, 0, FIGHT);
		}
	}
}

void	load_game(t_game *game)
{
	int	i;
	int	j;
	int	n_coin;

	game->mlx = mlx_init(WIDTH * game->map.width, HEIGHT * game->map.height,
			"so_long", false);
	if (!game->mlx)
		ft_error_map(&game->map, "could not load mlx");
	load_images(game);
	n_coin = 0;
	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
			draw_map(i, j, &n_coin, game);
	}
	i = -1;
	load_player_sprites(game);
}
