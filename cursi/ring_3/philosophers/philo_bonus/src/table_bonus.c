/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:46:28 by svilla-d          #+#    #+#             */
/*   Updated: 2024/07/19 10:18:14 by svilla-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_error_table(t_table *table, const char *message)
{
	printf("❌ Error ❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		printf("► %s\n", message);
	if (table)
	{
		if (table->sem)
		{
			if (table->sem->die && sem_close(table->sem->die) == -1)
				ft_error_table(NULL, "failed to close semaphore: die");
			sem_unlink("/die");
			if (table->sem->forks && sem_close(table->sem->forks) == -1)
				ft_error_philo(NULL, "failed to close semaphore: forks");
			sem_unlink("/forks");
			if (table->sem->print && sem_close(table->sem->print) == -1)
				ft_error_philo(NULL, "failed to close semaphore: print");
			sem_unlink("/print");
			free(table->sem);
		}
		if (table->monitor)
			free(table->monitor);
		free(table);
	}
	exit(EXIT_FAILURE);
}

void	ft_error_philo(t_philo *philos, const char *message)
{
	printf("❌ Error ❌\n");
	if (message != NULL && ft_strlen(message) != 0)
		printf("► %s\n", message);
	if (philos)
		free_philo(philos);
	exit(EXIT_FAILURE);
}

static void	parse_arguments(char **argv, t_table *table)
{
	table->seats = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		table->num_meals = ft_atoi(argv[5]);
	else
		table->num_meals = UNSET;
	table->dead = FALSE;
	table->sem = NULL;
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
	table->sem = init_semaphore(table);
	return (table);
}
