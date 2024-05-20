/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:35:08 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 19:56:35 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	update_direction(t_game *game, t_player_action action)
{
	if (action != STOP && action != FIGHT)
		game->player.direction = action;
}

void	perform_fight_action(t_game *game, int *x, int *y)
{
	if (game->player.direction == UP)
		*y = -1;
	else if (game->player.direction == DOWN)
		*y = 1;
	else if (game->player.direction == LEFT)
		*x = -1;
	else if (game->player.direction == RIGHT)
		*x = 1;
}

bool	handle_map_interaction(t_game *game, int x, int y, t_player_action act)
{
	int	py;
	int	px;

	py = game->player.y;
	px = game->player.x;
	if (game->map.value[py + y][px + x] == '1')
		return (false);
	if (game->map.value[py + y][px + x] == 'C')
		delete_coin(game, px + x, py + y);
	if (game->map.value[py + y][px + x] == 'M')
	{
		if (act == FIGHT)
			delete_enemy(game, px + x, py + y);
		else
		{
			game->player.is_alive = false;
			ft_printf("I'm sorry, you've been defeated\n");
			ft_printf("* Have you tried using SPACE? *\n");
		}
	}
	if (game->map.value[py][px] != 'E')
		game->map.value[py][px] = '0';
	if (game->map.value[py + y][px + x] != 'E')
		game->map.value[py + y][px + x] = 'P';
	return (true);
}

void	update_player_position(t_game *game, int x, int y, t_player_action act)
{
	int	py;
	int	px;
	int	sprite;

	py = game->player.y;
	px = game->player.x;
	game->player.img->instances[0].y = -HEIGHT;
	game->player.img->instances[0].x = -WIDTH;
	if (game->player.current_sprite == 3)
		game->player.current_sprite = -1;
	game->player.current_sprite++;
	sprite = game->player.current_sprite;
	if (!game->player.is_alive)
		act = DIED;
	if (act != FIGHT)
		game->player.img = game->player.sprites[act][sprite];
	else
		game->player.img = game->player.sprites[act][game->player.direction];
	game->player.img->instances[0].y = (py + y) * HEIGHT;
	game->player.img->instances[0].x = (px + x) * WIDTH;
	game->player.y += y;
	game->player.x += x;
}

void	check_game_status(t_game *game, t_player_action act)
{
	int				py;
	int				px;
	mlx_texture_t	*splash;
	mlx_image_t		*i;

	py = game->player.y;
	px = game->player.x;
	if (game->map.value[py][px] == 'E' && act != STOP)
	{
		if (game->total_coins == game->collected_coins)
		{
			ft_printf("Congrats! You have won in %d moves 🏆\n", game->moves);
			game->win = true;
			splash = mlx_load_png("./textures/dragon.png");
			i = mlx_texture_to_image(game->mlx, splash);
			mlx_image_to_window(game->mlx, i, game->map.width * WIDTH / 2 - 100,
				game->map.height * HEIGHT / 2 - 82);
			mlx_delete_texture(splash);
		}
		else
		{
			ft_printf("You must collect all the dragon balls (%d/%d)\n",
				game->collected_coins, game->total_coins);
		}
	}
}
