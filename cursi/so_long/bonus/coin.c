/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:17:18 by svilla-d          #+#    #+#             */
/*   Updated: 2024/06/20 13:43:59 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

char	*generate_coin_filename(void)
{
	char			*n;
	char			*filename;
	const size_t	size = 100;

	filename = ft_strndup("./textures/coins/", size);
	n = ft_itoa(rand() % COINS_TYPES + 1);
	ft_strlcat(filename, n, size);
	ft_strlcat(filename, ".png", size);
	free(n);
	return (filename);
}

void	load_simple_coin(t_game *game, int c, int i, int j)
{
	char	*filename;

	filename = generate_coin_filename();
	game->coin[c].texture = mlx_load_png(filename);
	if (!game->coin[c].texture)
		ft_error_game(game, "could not load texture");
	game->coin[c].img = mlx_texture_to_image(game->mlx,
			game->coin[c].texture);
	game->coin[c].x = j;
	game->coin[c].y = i;
	c++;
	free(filename);
}

void	load_coins(t_game *game)
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
			if (game->map.value[i][j] == 'C')
				load_simple_coin(game, c, i, j);
		}
	}
}

void	delete_coin(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < game->total_coins)
	{
		if (game->coin[i].x == x && game->coin[i].y == y)
		{
			mlx_delete_image(game->mlx, game->coin[i].img);
			mlx_delete_texture(game->coin[i].texture);
			game->coin[i].texture = NULL;
			game->collected_coins++;
		}
	}
	if (game->collected_coins == game->total_coins)
	{
		ft_printf("Great, you have found all the dragon balls. ");
		ft_printf("Now go to KameHouse to summon Shenlong (%d/%d)\n",
			game->collected_coins, game->total_coins);
	}
}

void	delete_all_coins(t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->total_coins)
	{
		if (game->coin[i].texture != NULL)
		{
			mlx_delete_image(game->mlx, game->coin[i].img);
			mlx_delete_texture(game->coin[i].texture);
		}
	}
}
