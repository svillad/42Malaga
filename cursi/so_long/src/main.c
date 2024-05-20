/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:17 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/20 12:01:54 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	play_game(t_game *game)
{
	mlx_key_hook(game->mlx, key_press_event, game);
	mlx_loop_hook(game->mlx, animation, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		ft_error_map(NULL, "number arguments is incorrect");
		return (0);
	}
	read_map(&game.map, argv[1]);
	init_parameters(&game);
	validate_path(&game);
	load_game(&game);
	play_game(&game);
	end_game(&game);
	return (EXIT_SUCCESS);
}
