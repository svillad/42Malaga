/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:46:28 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/19 10:17:47 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error_table(t_table *table, const char *message)
{
	printf("❌ Error ❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		printf("► %s\n", message);
	if (table)
	{
		if (table->forks)
			free(table->forks);
		if (table->mutex)
			delete_mutex(table);
		if (table->monitor)
			free(table->monitor);
		free(table);
	}
	exit(EXIT_FAILURE);
}

static void	parse_arguments(char **argv, t_table *table)
{
	int	i;

	table->seats = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->num_meals = ft_atoi(argv[5]);
	else
		table->num_meals = UNSET;
	table->dead = FALSE;
	table->forks = NULL;
	table->mutex = NULL;
	table->forks = (int *)malloc(table->seats * sizeof(int));
	if (!table->forks)
		ft_error_table(table, "failed to allocate memory: forks");
	i = -1;
	while (++i < table->seats)
		table->forks[i] = UNLOCK;
	table->monitor = (pthread_t *)malloc(table->seats * sizeof(pthread_t));
}

t_table	*init_table(char **argv)
{
	t_table	*table;

	table = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		ft_error_table(table, "failed to allocate memory");
	parse_arguments(argv, table);
	table->mutex = init_mutex(table);
	return (table);
}
