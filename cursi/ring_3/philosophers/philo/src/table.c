/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:46:28 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/09 12:43:48 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	int	i;

	if (table->forks != NULL)
		free(table->forks);
	if (table->mutex != NULL)
	{
		if (table->mutex->die != NULL)
			free(table->mutex->die);
		if (table->mutex->forks != NULL)
			free(table->mutex->forks);
		if (table->mutex->print != NULL)
			free(table->mutex->print);
		free(table->mutex);
	}
	if (table->philosophers != NULL)
	{
		i = -1;
		while (++i < table->seats)
			free(table->philosophers[i]);
		free(table->philosophers);
	}
}

static void	init_to_zero(t_table *table)
{
	table->seats = 0;
	table->time_to_die = 0;
	table->time_to_eat = 0;
	table->time_to_sleep = 0;
	table->num_meals = 0;
	table->dead = 0;
	table->forks = NULL;
	table->philosophers = NULL;
	table->mutex = NULL;
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
	table->forks = (int *)malloc(table->seats * sizeof(int));
	if (!table->forks)
		ft_error_philo(table, "failed to allocate memory: forks");
	i = -1;
	while (++i < table->seats)
		table->forks[i] = UNLOCK;
}

t_table	*init_table(char **argv)
{
	t_table	*table;

	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		ft_error_philo(table, "failed to allocate memory");
	init_to_zero(table);
	parse_arguments(argv, table);
	table->mutex = init_mutex(table);
	table->philosophers = init_philosophers(table);
	return (table);
}
