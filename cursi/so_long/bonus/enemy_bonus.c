/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:17:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/06/22 16:02:07 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*generate_enemy_filename(void)
{
	char			*n;
	char			*filename;
	const size_t	size = 100;

	filename = ft_strndup("./textures/enemies/", size);
	n = ft_itoa(rand() % ENEMIES_TYPES + 1);
	ft_strlcat(filename, n, size);
	ft_strlcat(filename, ".png", size);
	free(n);
	return (filename);
}

void	load_simple_enemy(t_game *game, int c, int i, int j)
{
	char	*filename;

	filename = generate_enemy_filename();
	game->enemy[c].texture = mlx_load_png(filename);
	if (!game->enemy[c].texture)
		ft_error_game(game, "could not load image: enemy");
	game->enemy[c].img = mlx_texture_to_image(game->mlx,
			game->enemy[c].texture);
	game->enemy[c].x = j;
	game->enemy[c].y = i;
	c++;
	free(filename);
}

void	load_enemies(t_game *game)
{
	int		i;
	int		j;
	int		c;

	i = -1;
	c = 0;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (game->map.value[i][j] == 'M')
				load_simple_enemy(game, c, i, j);
		}
	}
}

void	delete_enemy(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < game->total_enemies)
	{
		if (game->enemy[i].x == x && game->enemy[i].y == y)
		{
			mlx_delete_image(game->mlx, game->enemy[i].img);
			mlx_delete_texture(game->enemy[i].texture);
			game->enemy[i].texture = NULL;
		}
	}
}

void	delete_all_enemies(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->total_enemies)
	{
		if (game->enemy[i].texture != NULL)
		{
			mlx_delete_image(game->mlx, game->enemy[i].img);
			mlx_delete_texture(game->enemy[i].texture);
		}
	}
}
