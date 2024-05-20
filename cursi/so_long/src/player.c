/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:27:35 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 19:41:22 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, int x, int y, t_player_action action)
{
	game->player.time = 0;
	update_direction(game, action);
	if (action == FIGHT)
		perform_fight_action(game, &x, &y);
	if (handle_map_interaction(game, x, y) == false)
		return ;
	update_player_position(game, x, y, action);
	if (action != STOP)
	{
		game->moves++;
		ft_printf("%d\n", game->moves);
	}
	check_game_status(game, action);
}

char	*generate_player_filename(int i, t_player_action action)
{
	char			*n;
	char			*filename;
	const size_t	size = 100;

	filename = ft_strndup("./textures/player/goku_", size);
	if (action == UP)
		ft_strlcat(filename, "U", size);
	else if (action == DOWN)
		ft_strlcat(filename, "D", size);
	else if (action == LEFT)
		ft_strlcat(filename, "L", size);
	else if (action == RIGHT)
		ft_strlcat(filename, "R", size);
	else if (action == STOP)
		ft_strlcat(filename, "S", size);
	else if (action == FIGHT)
		ft_strlcat(filename, "F", size);
	n = ft_itoa(i + 1);
	ft_strlcat(filename, n, size);
	ft_strlcat(filename, ".png", size);
	free(n);
	return (filename);
}

void	load_action_images(t_game *game, t_player_action action)
{
	int		i;
	char	*filename;

	i = -1;
	while (++i < PLAYER_SPRITES)
	{
		filename = generate_player_filename(i, action);
		game->player.texture[action][i] = mlx_load_png(filename);
		game->player.sprites[action][i] = mlx_texture_to_image(game->mlx,
				game->player.texture[action][i]);
		mlx_image_to_window(game->mlx, game->player.sprites[action][i], -WIDTH,
			-HEIGHT);
		free(filename);
	}
}

void	load_player_sprites(t_game *game)
{
	game->player.is_alive = true;
	game->player.time = 0;
	game->player.current_sprite = 0;
	game->player.direction = UP;
	load_action_images(game, STOP);
	load_action_images(game, UP);
	load_action_images(game, DOWN);
	load_action_images(game, LEFT);
	load_action_images(game, RIGHT);
	load_action_images(game, FIGHT);
	game->player.img = game->player.sprites[STOP][0];
	game->player.img->instances[0].x = WIDTH * game->player.x;
	game->player.img->instances[0].y = HEIGHT * game->player.y;
}

void	delete_player(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < ACTIONS)
	{
		j = -1;
		while (++j < PLAYER_SPRITES)
		{
			mlx_delete_image(game->mlx, game->player.sprites[i][j]);
			mlx_delete_texture(game->player.texture[i][j]);
		}
	}
}
