/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:40:31 by svilla-d          #+#    #+#             */
/*   Updated: 2024/05/17 00:40:32 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->height)
		free(map->map[i]);
	if (map->map)
		free(map->map);
	map->map = NULL;
	map->height = 0;
	map->width = 0;
	map->capacity = 0;
}

void	ft_error_map(t_map *map, const char *message)
{
	ft_fprintf(STDERR_FILENO, "❌ERROR❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		ft_fprintf(STDERR_FILENO, "► %s\n", message);
	ft_free_map(map);
	exit(EXIT_FAILURE);
}

// write(1, "❌ERROR❌\n", 12);
// if (num > 7)
// 	ft_error2(d, num);
// if (num == 1)
// 	write(1, "►En el principio de linea no hay pared.🧱\n", 46);
// if (num == 2)
// 	write(1, "►En el final de linea no hay pared.🧱\n", 42);
// if (num == 3)
// 	write(1, "►En la primera linea no hay pared.🧱\n", 41);
// if (num == 4)
// 	write(1, "►En la ultima linea no hay pared.🧱\n", 40);
// if (d->consum < 1 && num == 5)
// 	write(1, "►No hay consumibles!\n", 21);
// if (d->player != 1 && num == 5)
// 	write(1, "►El mapa solo debe tener un personaje. 🚶🏻‍♂️\n", 59);
// if (d->ex < 1 && num == 5)
// 	write(1, "►El mapa debe contener una salida. \n", 38);
// if (num == 6)
// 	write(1, "►El fichero no tiene la extension correcta.\n", 46);
// if (num == 7)
// 	write(1, "►El mapa no es rectangular.\n", 30);
// if (num == 8)
// 	write(1, "►El mapa contiene caracteres erroneos.\n", 41);
// if (num == 9)
// 	write(1, "►El mapa no es rectangular\n", 29);